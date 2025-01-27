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
	ProjectileMovement->MaxSpeed = 300.0f;                // Velocidade máxima
	ProjectileMovement->InitialSpeed = 0.0f;            // Velocidade inicial
	ProjectileMovement->bConstrainToPlane = true;         // Movimento restringido a um plano
	ProjectileMovement->SetPlaneConstraintFromVectors(FVector(1, 0, 0), FVector(0, 1, 0)); // Apenas plano XY
	ProjectileMovement->bIsHomingProjectile = false;       // Ativa Homing para seguir "foot_r"
	ProjectileMovement->HomingAccelerationMagnitude = 5000.0f; // Magnitude de homing
	ProjectileMovement->Bounciness = 1.0f;
	ProjectileMovement->bSweepCollision = false;
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
	
}




void ABallStaticMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	// if (PlayerController) 
	// {
	// 	// Obtém o Pawn controlado pelo PlayerController
	// 	APawn* PlayerPawn = PlayerController->GetPawn();
	// 	if (PlayerPawn)
	// 	{
	// 		// Faz cast do Pawn para o PlayerCharacter (ou o tipo específico do seu personagem)
	// 		ACharacter* PlayerCharacter = Cast<ACharacter>(PlayerPawn); // Substitua ACharacter pelo seu PlayerCharacter personalizado
	//
	// 		const float BallRadius = 10.0f; // Altere conforme o tamanho da bola
	// 		float TravelDistance = PlayerCharacter->GetVelocity().Size() * DeltaTime;
	// 		float BallRotationRadians = TravelDistance / BallRadius;
	//
	// 		// Define o eixo de rotação baseado na direção do movimento
	// 		FVector VelocityNormalized = PlayerCharacter->GetVelocity().GetSafeNormal();
	// 		FVector RotationAxis = FVector::CrossProduct(FVector::UpVector, VelocityNormalized); // Eixo no plano XY
	// 		RotationAxis.Z = 22.5f; // Garante que só rotacione no plano XY
	// 		
	// 		// Calcula a rotação delta
	// 		FQuat RotationDelta = FQuat(RotationAxis, BallRotationRadians);
	// 		// Suaviza a rotação da bola usando interpolação
	// 		FQuat CurrentRotation = GetActorRotation().Quaternion();
	// 		FQuat TargetRotation = CurrentRotation * RotationDelta;
	// 		FQuat InterpolatedRotation = FQuat::Slerp(CurrentRotation, TargetRotation, 5.0f); // 0.1f é a velocidade da interpolação
	// 		SetActorTransform(FTransform(InterpolatedRotation, GetActorLocation(), FVector(1.1f, 1.1f, 1.1f)));
	// 	}
	// }
	
	
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
	CurrentBallComponent->RegisterComponent();

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
	PhysicsHandle->RegisterComponent();

	FloatingPawn = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
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
}
