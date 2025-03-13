// Fill out your copyright notice in the Description page of Project Settings.


#include "Application/BallStaticMeshActor/BallStaticMeshActor.h"

#include "Application/PlayerCharacter/PlayerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Services/CurrentBall/CurrentBallService.h"

ABallStaticMeshActor::ABallStaticMeshActor()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorScale3D(FVector(1.1f, 1.1f, 1.1f));
	
	SetupMesh();
	SetupComponents();

	RootComponent = GetStaticMeshComponent();

	// Componente de movimento do projétil
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
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
		ESelectClosestBoneCharacterEnum DefineBone = Character->ClosestBone->GetFoot();

		FVector FootBoneLocation = Character->GetMesh()->GetBoneLocation(TEXT("foot_l"), EBoneSpaces::WorldSpace);
		if (DefineBone == ESelectClosestBoneCharacterEnum::RightFoot)
		{
			FootBoneLocation = Character->GetMesh()->GetBoneLocation(TEXT("foot_r"), EBoneSpaces::WorldSpace);	
		}
		
		GetStaticMeshComponent()->AddAngularImpulseInRadians(FootBoneLocation.GetSafeNormal(), NAME_None, true);
		IsContact = true;
	}
}


void ABallStaticMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerController* PlayerController = nullptr;
	APlayerCharacter* Character = nullptr;

	if (GetWorld())
	{
		PlayerController = GetWorld()->GetFirstPlayerController();
	}

	if (PlayerController)
	{
		APawn* Pawn = PlayerController->GetPawn();
		if (Pawn)
		{
			Character = Cast<APlayerCharacter>(Pawn);
		}
	}

	if (Character)
	{
		if (
			Character->UpdateStateCharacterComponent->GetState() != EPlayerCharacterStateEnum::Controlling ||
			Character->UpdateStateCharacterComponent->GetState() != EPlayerCharacterStateEnum::ControllingTrajectoryChange
			)
		{
			IsContact = false;
		}
		
		if (IsContact)
		{
			FVector CurrentAngularVelocity = GetStaticMeshComponent()->GetPhysicsAngularVelocityInRadians();
			FVector SmoothedAngularVelocity = FMath::VInterpTo(CurrentAngularVelocity, GetActorLocation(), GetWorld()->GetDeltaSeconds(), 1.0f);
			GetStaticMeshComponent()->SetAllPhysicsAngularVelocityInRadians(SmoothedAngularVelocity);	
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
	GetStaticMeshComponent()->SetNotifyRigidBodyCollision(true);
	GetStaticMeshComponent()->SetPhysicsMaxAngularVelocityInDegrees(200.f);
	GetStaticMeshComponent()->SetAngularDamping(0.5f);
	GetStaticMeshComponent()->SetLinearDamping(0.5f);
}
