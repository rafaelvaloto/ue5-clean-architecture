// Fill out your copyright notice in the Description page of Project Settings.


#include "Application/PlayerController/JogPlayerController.h"

#include "DualSenseProxy.h"
#include "Application/PlayerCharacter/PlayerCharacter.h"
#include "NewProject/Public/UseCases/InputCharacterComponent/MovementCharacterUseCase.h"
#include "Camera/CameraActor.h"
#include "UseCases/InputCharacterComponent/ActionCharacterTackleSliderUseCase.h"
#include "UseCases/InputCharacterComponent/ActionCharacterTackleUseCase.h"
#include "UseCases/InputCharacterComponent/MovementCharacterControlYawUseCase.h"
#include "GameFramework/ForceFeedbackEffect.h"
#include "GameFramework/ForceFeedbackParameters.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "UseCases/CharacterControllBall/CharacterChangeAnimMontageDirectionUseCase.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Haptics/HapticFeedbackEffect_Base.h"


void AJogPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

AJogPlayerController::AJogPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bForceFeedbackEnabled = true;

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

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionTackleSliderAsset(
		TEXT("/Game/Input/IA_TackleSlider.IA_TackleSlider"));
	if (InputActionTackleSliderAsset.Succeeded())
	{
		IA_TackleSlider = InputActionTackleSliderAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionControllRigthAsset(
		TEXT("/Game/Input/IA_ControllRigth.IA_ControllRigth"));
	if (InputActionControllRigthAsset.Succeeded())
	{
		IA_ControllRigth = InputActionControllRigthAsset.Object;
	}
}

void AJogPlayerController::SetDisableHaptics(bool bNewDisabled)
{
	Super::SetDisableHaptics(bNewDisabled);
}

void AJogPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// Defina uma câmera fixa em um ponto específico
	bAutoManageActiveCameraTarget = true;
	
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
			FixedCamera->GetCameraComponent()->AspectRatio = ViewportSize.X / ViewportSize.Y;
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

	SetupDevice();
}

void AJogPlayerController::SetupDevice()
{
	SetDisableHaptics(false);
	if (
		!UDualSenseProxy::DeviceIsConnected(0) && !UDualSenseProxy::DeviceReconnect(0)
		)
	{
		return;
	}

	UDualSenseProxy::ResetEffects(0);
	UDualSenseProxy::LedColorEffects(0, FColor::White);
	UDualSenseProxy::LedPlayerEffects(0, ELedPlayerEnum::One, ELedBrightnessEnum::Low);
}

void AJogPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInputComponent)
	{
		return;
	}

	// Locomotion
	EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AJogPlayerController::Move);
	EnhancedInputComponent->BindAction(IA_ControllRigth, ETriggerEvent::Triggered, this,
	                                   &AJogPlayerController::ControllRigth);


	EnhancedInputComponent->BindAction(IA_ControlRotation, ETriggerEvent::Triggered, this,
	                                   &AJogPlayerController::ControllRotation);
	EnhancedInputComponent->BindAction(IA_ControlRotation, ETriggerEvent::Completed, this,
	                                   &AJogPlayerController::ControllRotationCanceled);


	// Actions  
	EnhancedInputComponent->BindAction(IA_Tackle, ETriggerEvent::Triggered, this, &AJogPlayerController::Tackle);
	EnhancedInputComponent->BindAction(IA_TackleSlider, ETriggerEvent::Triggered, this,
	                                   &AJogPlayerController::TackleSlider);
}

void AJogPlayerController::TackleSlider(const FInputActionValue& InputController)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter not found"));
		return;
	}
	UActionCharacterTackleSliderUseCase::Handle(
		PlayerCharacter->ClosestBone,
		PlayerCharacter->PlayAnimMontageComponent,
		PlayerCharacter->UpdateStateCharacterComponent,
		PlayerCharacter->SelectorPoseSearchDatabaseComponent,
		true
	);
}

void AJogPlayerController::Tackle(const FInputActionValue& InputController)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter not found"));
		return;
	}

	UActionCharacterTackleUseCase::Handle(
		PlayerCharacter->ClosestBone,
		PlayerCharacter->PlayAnimMontageComponent,
		PlayerCharacter->UpdateStateCharacterComponent,
		PlayerCharacter->SelectorPoseSearchDatabaseComponent,
		true
	);
}

void AJogPlayerController::ControllRotationCanceled(const FInputActionValue& InputController)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (!PlayerCharacter)
	{
		return;
	}

	UMovementCharacterControlYawUseCase::Handle(PlayerCharacter->MovementPlayerCharacter, PlayerCharacter->UpdateStateCharacterComponent, 0.0f);
}

void AJogPlayerController::ControllRotation(const FInputActionValue& InputController)
{
	float InputVector = InputController.Get<float>();
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (!PlayerCharacter)
	{
		return;
	}
	
	UMovementCharacterControlYawUseCase::Handle(PlayerCharacter->MovementPlayerCharacter, PlayerCharacter->UpdateStateCharacterComponent, InputVector);
}

void AJogPlayerController::ControllRigth(const FInputActionValue& InputController)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (!PlayerCharacter)
	{
		return;
	}

	FVector InputVector = InputController.Get<FVector>();
	UCharacterChangeAnimMontageDirectionUseCase::Handle(
			PlayerCharacter->ClosestBone,
			PlayerCharacter->UpdatedBaseAttributesComponent,
			PlayerCharacter->UpdateStateCharacterComponent,
			PlayerCharacter->PlayAnimMontageComponent,
			PlayerCharacter->SelectorPoseSearchDatabaseComponent,
			InputVector
		);
}

void AJogPlayerController::Move(const FInputActionValue& InputController)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (!PlayerCharacter)
	{
		return;
	}

	FVector InputVector = InputController.Get<FVector>();
	UMovementCharacterUseCase::Handle(PlayerCharacter->MovementPlayerCharacter, InputVector);
}
