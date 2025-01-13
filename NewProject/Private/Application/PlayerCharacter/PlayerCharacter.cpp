// Fill out your copyright notice in the Description page of Project Settings.


#include "Application/PlayerCharacter/PlayerCharacter.h"
#include "Components/Character/InputCharacterComponent.h"
#include "Components/Character/UpdateAttributesCharacterComponent.h"
#include "Components/Character/UpdateStateCharacterComponent.h"
#include "Components/Character/UpdateTrajectoryCharacterComponent.h"
#include "Components/MotionMatchHelpers/SelectorPoseSearchDatabaseComponent.h"
#include "UseCases/CharacterTrajectoryComponent/CharacterTrajectoryComponentUseCase.h"
#include "UseCases/UpdateStateCharacterComponent/UpdateStateCharacterComponentUseCase.h"
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
	SetupAnimInstanceBlueprint();

	bUseControllerRotationYaw = false;
	bIsUpdatedYawControlChanged = false;

	GetCharacterMovement()->MinAnalogWalkSpeed = 5.00f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MaxAcceleration = 1000.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 100.0f;

	GetRootComponent()->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));
}

void APlayerCharacter::UpdateYawMovementRoot(const bool Value)
{
	bIsUpdatedYawControlChanged = Value;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotação baseada no movimento.
	GetCharacterMovement()->bUseControllerDesiredRotation = false; // Ignore o ControlRotation

	SelectorPoseSearchDatabaseComponent->LoadDatabaseAsset(
		"C:\\Users\\rafae\\Documents\\Unreal Projects\\NewProject\\Source\\NewProject\\Entities\\PoseSearchDatabases"
	);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Update Movemnt condition
	UpdateMovementMode(DeltaTime);

	// Update Persistent Attrs Character, Velocity, Location etc..
	UUpdateAttributesCharacterComponentUseCase::Handle(UpdatedBaseAttributesComponent, this);

	// Update Machine State Character, Idle, Walk etc..
	UUpdateStateCharacterComponentUseCase::Handle(UpdateStateCharacterComponent, UpdatedBaseAttributesComponent);

	// Update Character Trajectory Component
	UCharacterTrajectoryComponentUseCase::Handle(TrajectoryComponent, UpdatedBaseAttributesComponent, DeltaTime);
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
	SelectorPoseSearchDatabaseComponent->DefaultDatabaseAsset(
		"/Game/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Databases/Dense/PSD_Dense_Stand_Idles.PSD_Dense_Stand_Idles"
	);
	SelectorPoseSearchDatabaseComponent->RegisterComponent();
	// End Component Initialize PoseSearch Databses
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
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClass(
		TEXT("/Game/Characters/UEFN_Mannequin/Meshes/SK_UEFN_Mannequin_AnimBlueprint"));
	if (!AnimInstanceClass.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("AnimInstanceClass not found"));
		return;
	}

	GetMesh()->SetAnimInstanceClass(AnimInstanceClass.Class);
}

void APlayerCharacter::UpdateMovementMode(const float DeltaTime) const
{
	// Defina velocidades realistas
	const float RunSpeed = 500.0f; // Velocidade para correr
	const float AccelerationValue = 1000.0f; // Aceleração realista
	const float DecelerationValue = 100.0f; // Desaceleração realista

	// Checa o estado atual do personagem (por exemplo, Walk ou Run)
	// if (UpdateStateCharacterComponent->GetState() == EPlayerCharacterStateEnum::Running)
	// {
	// 	// O personagem está correndo
	// 	GetCharacterMovement()->MaxWalkSpeed = FMath::FInterpTo(
	// 		GetCharacterMovement()->MaxWalkSpeed,
	// 		RunSpeed,
	// 		DeltaTime,
	// 		5.0f // Velocidade de interpolação
	// 	);
	//
	// 	GetCharacterMovement()->MaxAcceleration = AccelerationValue;
	// 	GetCharacterMovement()->BrakingDecelerationWalking = DecelerationValue;
	// 	return;
	// }
	//
	// O personagem está andando
	GetCharacterMovement()->MaxWalkSpeed = FMath::FInterpTo(
		GetCharacterMovement()->MaxWalkSpeed,
		RunSpeed,
		DeltaTime,
		5.0f
	);

	// Configura aceleração e desaceleração de forma independente
	GetCharacterMovement()->MaxAcceleration = AccelerationValue;
	GetCharacterMovement()->BrakingDecelerationWalking = DecelerationValue;
}
