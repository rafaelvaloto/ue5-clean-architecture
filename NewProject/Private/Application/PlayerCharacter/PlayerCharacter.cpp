// Fill out your copyright notice in the Description page of Project Settings.


#include "Application/PlayerCharacter/PlayerCharacter.h"
#include "Components/Character/InputCharacterComponent.h"
#include "Components/Character/UpdateAttributesCharacterComponent.h"
#include "Components/Character/UpdateStateCharacterComponent.h"
#include "Components/Character/UpdateTrajectoryCharacterComponent.h"
#include "Components/MotionMatchHelpers/SelectorPoseSearchDatabaseComponent.h"
#include "UseCases/CharacterTrajectoryComponent/CharacterTrajectoryComponentUseCase.h"
#include "UseCases/UpdateStateCharacterComponent/UpdateStateCharacterComponentUseCase.h"
#include "UseCases/SelectorPoseSearchDatabaseComponent/UpdateNodePoseSearchDatabaseUseCase.h"
#include "UseCases/UpdateAttributesCharacterComponent/UpdateAttributesCharacterComponentUseCase.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Init Components
	SetupComponents();
	SetupSkeletonMesh();
	SetupCameraComponents();
	SetupAnimInstanceBlueprint();

	bUseControllerRotationYaw = false;

	// Configs GetCharacterMovement()
	GetCharacterMovement()->bIgnoreBaseRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	GetCharacterMovement()->MaxWalkSpeed = 201.f;
	GetCharacterMovement()->MaxAcceleration = 200.f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (SelectorPoseSearchDatabaseComponent)
	{
		// Update Machine State Character, Idle, Walk etc..
		UUpdateNodePoseSearchDatabaseUseCase::Handle(SelectorPoseSearchDatabaseComponent);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (UpdateStateCharacterComponent->GetState() == EPlayerCharacterStateEnum::Running)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
	}

	if (UpdateStateCharacterComponent->GetState() != EPlayerCharacterStateEnum::Running)
	{
		GetCharacterMovement()->MaxWalkSpeed = 201.f;
	}

	// Update Persistent Attrs Character, Velocity, Location etc..
	UUpdateAttributesCharacterComponentUseCase::Handle(UpdatedBaseAttributesComponent, this);

	// Update Character Trajectory Component
	UCharacterTrajectoryComponentUseCase::Handle(TrajectoryComponent, UpdatedBaseAttributesComponent, DeltaTime);

	// Update Machine State Character, Idle, Walk etc..
	UUpdateStateCharacterComponentUseCase::Handle(UpdateStateCharacterComponent, UpdatedBaseAttributesComponent);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::SetupComponents()
{
	// UCharacterTrajectoryComponent Component Plugin
	TrajectoryComponent = CreateDefaultSubobject<UUpdateTrajectoryCharacterComponent>(TEXT("TrajectoryComponent"));
	TrajectoryComponent->RegisterComponent();

	// Inicializa o componente que recebe a entrada do controle e insere a movimentação no Character
	MovementPlayerCharacter = CreateDefaultSubobject<UInputCharacterComponent>(TEXT("ICustomMovementComponent"));
	MovementPlayerCharacter->RegisterComponent();

	// Inicialize o componente que atualiza os atributos do Character, Velocity etc..
	UpdatedBaseAttributesComponent = CreateDefaultSubobject<UUpdateAttributesCharacterComponent>(
		TEXT("IUpdatedBaseAttributesComponentInterface"));
	UpdatedBaseAttributesComponent->RegisterComponent();

	// Inicialize o componente que atualiza o estado de Character, Idle, Walk etc..  
	UpdateStateCharacterComponent = CreateDefaultSubobject<UUpdateStateCharacterComponent>(
		TEXT("IUpdateStateCharacterComponentInterface"));
	UpdateStateCharacterComponent->RegisterComponent();

	// Inicialize o componente que atualiza o PoseSearchDatabases no nó MotionMatch em AnimBlueprint
	SelectorPoseSearchDatabaseComponent = CreateDefaultSubobject<USelectorPoseSearchDatabaseComponent>(
		TEXT("ISelectorPoseSearchDatabaseComponent"));
	SelectorPoseSearchDatabaseComponent->RegisterComponent();
}

void APlayerCharacter::SetupCameraComponents()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	SpringArmComponent->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArmComponent->TargetArmLength = 1200.f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	CameraComponent->AddLocalOffset(FVector(-400.f, 0.f, 550.f));
	CameraComponent->AddRelativeRotation(FRotator(-40.f, 0.f, 0.f));
}

void APlayerCharacter::SetupSkeletonMesh() const
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletonMesh(TEXT(
		"/Script/Engine.SkeletalMesh'/Game/Characters/UEFN_Mannequin/Meshes/SKM_UEFN_Mannequin.SKM_UEFN_Mannequin'"));
	if (!SkeletonMesh.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("SkeletonMesh not found"));
		return;
	}

	GetMesh()->SetSkeletalMesh(SkeletonMesh.Object);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}

void APlayerCharacter::SetupAnimInstanceBlueprint() const
{
	// Define a classe de AnimInstance no SkeletalMesh
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClass(TEXT("/Game/Blueprints/NewAnimBlueprint"));
	if (!AnimInstanceClass.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("AnimInstanceClass not found"));
		return;
	}

	GetMesh()->SetAnimInstanceClass(AnimInstanceClass.Class);
}
