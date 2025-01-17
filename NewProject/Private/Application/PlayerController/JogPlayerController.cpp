// Fill out your copyright notice in the Description page of Project Settings.


#include "Application/PlayerController/JogPlayerController.h"
#include "Application/PlayerCharacter/PlayerCharacter.h"
#include "NewProject/Public/UseCases/InputCharacterComponent/MovementCharacterUseCase.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Camera/CameraActor.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "UseCases/InputCharacterComponent/MovementCharacterControlYawUseCase.h"


AJogPlayerController::AJogPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContext(
		TEXT("/Game/Input/IMC_GDCMotionMatching.IMC_GDCMotionMatching"));
	if (InputMappingContext.Succeeded())
	{
		IMC_Default = InputMappingContext.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveAsset(
		TEXT("/Game/Input/IA_Move.IA_Move"));
	if (InputActionMoveAsset.Succeeded())
	{
		IA_Move = InputActionMoveAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionControlRotationAsset(
		TEXT("/Game/Input/IA_Control_Rotation.IA_Control_Rotation"));
	if (InputActionControlRotationAsset.Succeeded())
	{
		IA_ControlRotation = InputActionControlRotationAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionTackleAsset(
		TEXT("/Game/Input/IA_Tackle.IA_Tackle"));
	if (InputActionTackleAsset.Succeeded())
	{
		IA_Tackle = InputActionTackleAsset.Object;
	}

	
}

void AJogPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Defina uma câmera fixa em um ponto específico
	bAutoManageActiveCameraTarget = true;
	
	// Criar a câmera fixa (ou use um ACameraActor específico do cenário)
	FVector FixedCameraLocation(600.0f, 0.0f, 600.0f);
	FRotator FixedCameraRotation(-40.f, -180.0f, 0.0);

	ACameraActor* FixedCamera = GetWorld()->SpawnActor<ACameraActor>(FixedCameraLocation, FixedCameraRotation);
	if (FixedCamera)
	{
		FVector2D ViewportSize;
		if (GEngine && GEngine->GameViewport)
		{
			GEngine->GameViewport->GetViewportSize(ViewportSize);

			UE_LOG(LogTemp, Error, TEXT("ViewportSize: %f, %f"), ViewportSize.X, ViewportSize.Y)
		}
		
		// Definindo a câmera como a visão atual
		SetViewTarget(FixedCamera);
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(IMC_Default, 0);
	}
}

void AJogPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("EnhancedInputComponent not found, Cast InputComponent"));
		return;
	}

	EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AJogPlayerController::Move);
	EnhancedInputComponent->BindAction(IA_ControlRotation, ETriggerEvent::Triggered, this, &AJogPlayerController::ControllRotation);
	EnhancedInputComponent->BindAction(IA_ControlRotation, ETriggerEvent::Canceled, this, &AJogPlayerController::ControllRotationCanceled);
	EnhancedInputComponent->BindAction(IA_ControlRotation, ETriggerEvent::Canceled, this, &AJogPlayerController::ControllRotationCanceled);
	EnhancedInputComponent->BindAction(IA_Tackle, ETriggerEvent::Triggered, this, &AJogPlayerController::Tackle);
}

void AJogPlayerController::Tackle(const FInputActionValue& InputController)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter not found"));
		return;
	}

	if (PlayerCharacter->UpdateStateCharacterComponent->GetState() != EPlayerCharacterStateEnum::Tackle)
	{
		PlayerCharacter->SelectorPoseSearchDatabaseComponent->WaitingNotifyAnim = EWaitingNotifyAnimEnum::Waiting;
		PlayerCharacter->UpdateStateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::Tackle);
	}
}
void AJogPlayerController::ControllRotationCanceled(const FInputActionValue& InputController)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter not found"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Canceled"));
	
	UMovementCharacterControlYawUseCase::Handle(PlayerCharacter->MovementPlayerCharacter, 0.0f);
}
void AJogPlayerController::ControllRotation(const FInputActionValue& InputController)
{
	float InputVector = InputController.Get<float>();

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter not found"));
		return;
	}
	
	UMovementCharacterControlYawUseCase::Handle(PlayerCharacter->MovementPlayerCharacter, InputVector);
	UE_LOG(LogTemp, Warning, TEXT("ControllRotation %f"), InputVector);
}

void AJogPlayerController::Move(const FInputActionValue& InputController)
{
	
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter not found"));
		return;
	}

	FVector InputVector = InputController.Get<FVector>();
	UMovementCharacterUseCase::Handle(PlayerCharacter->MovementPlayerCharacter, InputVector);
}
