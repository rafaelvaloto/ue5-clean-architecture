// Fill out your copyright notice in the Description page of Project Settings.


#include "Application/BallStaticMeshActor/BallStaticMeshActor.h"

#include "Application/PlayerCharacter/PlayerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Services/CurrentBall/CurrentBallService.h"

// Sets default values
ABallStaticMeshActor::ABallStaticMeshActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetActorScale3D(FVector(1.1f, 1.1f, 1.1f));
	
	SetupMesh();
	RootComponent = GetStaticMeshComponent();

	SetupComponents();

	// Componente de movimento do projétil
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bShouldBounce = true;             // Sem efeitos de quicar
	ProjectileMovement->Friction = 0.0f;               // Sem atrito adicional
	ProjectileMovement->ProjectileGravityScale = 0.0f; // Gravidade customizada
	ProjectileMovement->MaxSpeed = 200.0f;                // Velocidade máxima
	ProjectileMovement->InitialSpeed = 0.0f;            // Velocidade inicial
	ProjectileMovement->bConstrainToPlane = true;         // Movimento restringido a um plano
	ProjectileMovement->SetPlaneConstraintFromVectors(FVector(1, 0, 0), FVector(0, 1, 0)); // Apenas plano XY
	ProjectileMovement->bIsHomingProjectile = false;       // Ativa Homing para seguir "foot_r"
	ProjectileMovement->HomingAccelerationMagnitude = 5000.0f; // Magnitude de homing
	ProjectileMovement->Bounciness = 1.0f;
	ProjectileMovement->bSweepCollision = true;
	ProjectileMovement->bRotationFollowsVelocity = true; // Seguir a rotação com base na direção
	
}

void ABallStaticMeshActor::BeginPlay()
{
	Super::BeginPlay();
	SetupServices();

	GetStaticMeshComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABallStaticMeshActor::OnOverlapBegin);
}

void ABallStaticMeshActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
										  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
										  const FHitResult& SweepResult)
{

	if (OtherActor == nullptr)
	{
		return;
	}

	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		IsContact = true;
		APlayerCharacter* Character = Cast<APlayerCharacter>(OtherActor);

		DrawDebugSphere(
				GetWorld(),
				SweepResult.ImpactPoint,       // Posição
				10.0f,                         // Raio da esfera
				12,                            // Resolução (número de segmentos)
				FColor::Red,                   // Cor
				false,                         // Persistente (desenho permanentemente ou temporariamente)
				5.0f                           // Tempo de vida da esfera (5 segundos)
			);
		
		// Calcula a nova posição da bola com base no pé do jogador
		ESelectClosestBoneCharacterEnum DefineBone = Character->ClosestBone->GetFoot();

		FVector FootBoneLocation = Character->GetMesh()->GetBoneLocation(TEXT("foot_l"), EBoneSpaces::WorldSpace);
		if (DefineBone == ESelectClosestBoneCharacterEnum::RightFoot)
		{
			UE_LOG(LogTemp, Warning, TEXT("FootBone r in ball"));
			FootBoneLocation = Character->GetMesh()->GetBoneLocation(TEXT("foot_r"), EBoneSpaces::WorldSpace);	
		}
					
		GetStaticMeshComponent()->AddTorqueInRadians(FootBoneLocation.GetSafeNormal() * 500.0f);
	}
}


void ABallStaticMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerCharacter* Character = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (Character) 
	{
		float Distance = FVector::Dist(GetActorLocation(), Character->GetActorLocation());

		// Ajusta os valores de amortecimento com base na distância
		if (Distance > 150.0f) // Exemplo: se estiver a menos de 200 unidades
		{
			UE_LOG(LogTemp, Warning, TEXT("Distance %f"), Distance);
			GetStaticMeshComponent()->SetAngularDamping(1.0f); // Maior amortecimento angular
			GetStaticMeshComponent()->SetLinearDamping(1.0f);  // Maior amortecimento linear
			IsContact = false;
		}
		else if (Distance > 90.0f) // Exemplo: se estiver a menos de 200 unidades
		{
			UE_LOG(LogTemp, Warning, TEXT("Distance Normal %f"), Distance);
			GetStaticMeshComponent()->SetAngularDamping(2.5f); // Valores padrão
			GetStaticMeshComponent()->SetLinearDamping(2.0f);
		}
		else
		{
			GetStaticMeshComponent()->SetAngularDamping(2.0f);
			GetStaticMeshComponent()->SetLinearDamping(1.0f);
		}
		
		
		if (Character->UpdateStateCharacterComponent->GetState() != EPlayerCharacterStateEnum::Controlling)
		{
			IsContact = false;
		}
		
		if (
			Character->UpdateStateCharacterComponent->GetState() == EPlayerCharacterStateEnum::Controlling &&
			IsContact
			)
		{
			// Calcula a direção do torque tentando limitar rotação cumulativa
			FVector TargetAngularVelocity = Character->LastPosition * 70.f;

			// GetCurrentAngularVelocity método fictício para obter velocidades atuais de rotação do objeto
			FVector CurrentAngularVelocity = GetStaticMeshComponent()->GetPhysicsAngularVelocityInRadians();

			// Suavização da velocidade angular para evitar "soma cumulativa violenta"
			FVector SmoothedAngularVelocity = FMath::VInterpTo(CurrentAngularVelocity, TargetAngularVelocity, GetWorld()->GetDeltaSeconds(), 1.0f);
			GetStaticMeshComponent()->SetPhysicsAngularVelocityInRadians(SmoothedAngularVelocity);
		}
	}
	
	
}

void ABallStaticMeshActor::SetupServices() const
{
	if (ICurrentBallComponentInterface* BallComponent = this->FindComponentByClass<UCurrentBallComponent>())
	{
		UCurrentBallService::RegisterService(BallComponent);
	}
}

void ABallStaticMeshActor::SetupComponents()
{
	CurrentBallComponent = CreateDefaultSubobject<UCurrentBallComponent>(TEXT("CurrentBall"));
	CurrentBallComponent->Activate(false);
	CurrentBallComponent->RegisterComponent();

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
	PhysicsHandle->Activate(false);
	PhysicsHandle->RegisterComponent();

	FloatingPawn = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
	FloatingPawn->Activate(false);
	FloatingPawn->RegisterComponent();
}

void ABallStaticMeshActor::SetupMesh() const
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BallStaticMesh(
		TEXT("/Script/Engine.StaticMesh'/Game/Soccer_set_1/Mesh/SM_soccer_ball_3.SM_soccer_ball_3'"));
	if (BallStaticMesh.Succeeded())
	{
		GetStaticMeshComponent()->SetStaticMesh(BallStaticMesh.Object);
		GetStaticMeshComponent()->SetMassOverrideInKg(NAME_None, 0.450f);
	}

	
	GetStaticMeshComponent()->SetEnableGravity(true);
	GetStaticMeshComponent()->SetSimulatePhysics(true);
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	GetStaticMeshComponent()->SetCollisionProfileName("BallOverlapProfile");
	GetStaticMeshComponent()->SetGenerateOverlapEvents(true);
	GetStaticMeshComponent()->SetNotifyRigidBodyCollision(false);
	GetStaticMeshComponent()->SetPhysicsMaxAngularVelocityInDegrees(70.f);
	GetStaticMeshComponent()->SetAngularDamping(2.0f);
	GetStaticMeshComponent()->SetLinearDamping(1.0f);
}
