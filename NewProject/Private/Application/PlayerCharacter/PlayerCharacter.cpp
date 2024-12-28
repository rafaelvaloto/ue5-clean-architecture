// Fill out your copyright notice in the Description page of Project Settings.


#include "Application/PlayerCharacter/PlayerCharacter.h"
#include "Components/Character/InputCharacterComponent.h"
#include "Components/Character/UpdateAttributesCharacterComponent.h"
#include "Components/Character/UpdateStateCharacterComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NewProject/Public/UseCases/UpdateAttributesCharacterComponent/UpdateAttributesCharacterComponentUseCase.h"
#include "UseCases/UpdateStateCharacterComponent/UpdateStateCharacterComponentUseCase.h"

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

	// Configs GetCharacterMovement()
	GetCharacterMovement()->bIgnoreBaseRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	SelectChoose = true;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UUpdateAttributesCharacterComponentUseCase::Handle(UpdatedBaseAttributesComponent, this);
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
	TrajectoryComponent = CreateDefaultSubobject<UCharacterTrajectoryComponent>(TEXT("TrajectoryComponent"));
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
