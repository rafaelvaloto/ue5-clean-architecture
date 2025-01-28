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
		APlayerCharacter* Character = Cast<APlayerCharacter>(OtherActor);
		UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));
		UE_LOG(LogTemp, Warning, TEXT("SweepResult %s"), *SweepResult.ToString());
		UE_LOG(LogTemp, Warning, TEXT("OtherComp %s"), *OtherComp->GetName());

		DrawDebugSphere(
				GetWorld(),
				SweepResult.ImpactPoint,       // Posição
				10.0f,                         // Raio da esfera
				12,                            // Resolução (número de segmentos)
				FColor::Red,                   // Cor
				false,                         // Persistente (desenho permanentemente ou temporariamente)
				5.0f                           // Tempo de vida da esfera (5 segundos)
			);

		FRotator PlayerRotation = Character->GetActorRotation();
		FVector PlayerLocation = Character->GetActorLocation();
		
		// Calcula a nova posição da bola com base no pé do jogador
		FVector TargetLocation = PlayerLocation + (PlayerRotation.Vector() * 100.0f); // Ajuste de 50 unidades
		FVector SmoothedLocation = FMath::VInterpTo(GetActorLocation(), FVector(TargetLocation.X, TargetLocation.Y, GetActorLocation().Z), GetWorld()->GetDeltaSeconds(), 5.0f); // 10.0f é a rapidez da suavização
		SetActorLocation(SmoothedLocation);
		
		UE_LOG(LogTemp, Warning, TEXT("LastPosition %s"), *Character->LastPosition.ToString());
		GetStaticMeshComponent()->AddTorqueInRadians(Character->LastPosition * 4000.f, NAME_None, false);
	}
}


void ABallStaticMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerCharacter* Character = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (Character) 
	{
		if (Character->UpdateStateCharacterComponent->GetState() == EPlayerCharacterStateEnum::Controlling)
		{
			// Calcula a direção do torque tentando limitar rotação cumulativa
			FVector TargetAngularVelocity = Character->LastPosition * 100.f;

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
	GetStaticMeshComponent()->SetPhysicsMaxAngularVelocityInDegrees(100.f);
	GetStaticMeshComponent()->SetAngularDamping(3.0f);
	GetStaticMeshComponent()->SetLinearDamping(0.5f);
}
