// Fill out your copyright notice in the Description page of Project Settings.


#include "Application/PlayerCharacter/PlayerCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/Character/InputCharacterComponent.h"
#include "Components/Character/PlayAnimMontageComponent.h"
#include "Components/Character/UpdateAttributesCharacterComponent.h"
#include "Components/Character/UpdateStateCharacterComponent.h"
#include "Components/Character/UpdateTrajectoryCharacterComponent.h"
#include "Components/MotionMatchHelpers/SelectorPoseSearchDatabaseComponent.h"
#include "UseCases/CharacterTrajectoryComponent/CharacterTrajectoryComponentUseCase.h"
#include "UseCases/UpdateStateCharacterComponent/UpdateStateCharacterComponentUseCase.h"
#include "UseCases/UpdateAttributesCharacterComponent/UpdateAttributesCharacterComponentUseCase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UseCases/CharacterControllBall/CharacterControllBallUseCase.h"

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
	GetCharacterMovement()->MinAnalogWalkSpeed = 5.00f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MaxAcceleration = 1000.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 100.0f;

	GetRootComponent()->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));
}


// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->SetVisibility(true);
	GetCapsuleComponent()->SetHiddenInGame(false);

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


	if (StartInpulse)
	{
		const FRotator CharacterRotation = GetOwner()->GetActorRotation(); // Rotação do personagem
		const FVector TargetImpulse = CharacterRotation.Vector() * 600.0f; // Ajuste o valor como necessário
		LaunchCharacter(
			FMath::VInterpTo(GetOwner()->GetVelocity(), TargetImpulse, DeltaTime, 5.0f),
			true,
			true
		);
	}

	UCharacterControllBallUseCase::Handle(
		SweepByChannel,
		ClosestBone,
		UpdateStateCharacterComponent,
		PlayAnimMontageComponent,
		SelectorPoseSearchDatabaseComponent
	);

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

	SweepByChannel = CreateDefaultSubobject<USweepByChannelComponent>(TEXT("SweepByChannelComponent"));
	SweepByChannel->DebugDrawLines(true);
	SweepByChannel->RegisterComponent();

	// UCharacterTrajectoryComponent Component Plugin
	TrajectoryComponent = CreateDefaultSubobject<UUpdateTrajectoryCharacterComponent>(TEXT("TrajectoryComponent"));
	TrajectoryComponent->RegisterComponent();

	ClosestBone = CreateDefaultSubobject<USelectClosestBoneCharacterComponent>(TEXT("SelectClesestBone"));
	ClosestBone->RegisterComponent();

	PlayAnimMontageComponent = CreateDefaultSubobject<UPlayAnimMontageComponent>(TEXT("AnimationComponent"));
	PlayAnimMontageComponent->RegisterComponent();

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
	GetMesh()->SetCollisionProfileName("CharacterProfile");
	GetMesh()->SetGenerateOverlapEvents(true);
}

void APlayerCharacter::SetupAnimInstanceBlueprint() const
{
	// Define a classe de AnimInstance no SkeletalMesh
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassAsset(
		TEXT("/Game/Blueprints/ABP_SK_UEFN_Manequin_AminBlueprint"));
	if (!AnimInstanceClassAsset.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("AnimInstanceClass not found"));
		return;
	}

	GetMesh()->SetAnimInstanceClass(AnimInstanceClassAsset.Class);
}
