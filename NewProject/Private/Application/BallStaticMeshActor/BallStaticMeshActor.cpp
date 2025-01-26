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

void ABallStaticMeshActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                          const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Colisão detectada com: %s"), *OtherActor->GetName());
	}
}

void ABallStaticMeshActor::BeginPlay()
{
	Super::BeginPlay();
	SetupServices();
}


void ABallStaticMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
