// Fill out your copyright notice in the Description page of Project Settings.


#include "Application/PlayerController/JogPlayerController.h"
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

#ifndef WINDOWS_PLATFORM_TYPES_GUARD
   #include "Windows/AllowWindowsPlatformTypes.h"
#endif

#include <dinput.h>  // Inclui o cabeçalho do DirectInput
// Your Windows-specific code here...

#ifdef WINDOWS_PLATFORM_TYPES_GUARD
   #include "Windows/HideWindowsPlatformTypes.h"
#endif

#include <XInput.h>

#include "Windows/AllowWindowsPlatformTypes.h" // Correct relative path

LPDIRECTINPUT8 g_pDirectInput = NULL;          // Ponteiro para o objeto DirectInput
LPDIRECTINPUTDEVICE8 g_pGamepad = NULL;


HWND GetGameWindowHandle()
{
	if (GEngine && GEngine->GameViewport)
	{
		TSharedPtr<SWindow> Window = GEngine->GameViewport->GetWindow();
		if (Window.IsValid())
		{
			return static_cast<HWND>(Window->GetNativeWindow()->GetOSWindowHandle());
		}
	}

	return nullptr;
}

void AJogPlayerController::InitializeDirectInput(HWND hwnd)
{
	// Inicializar o DirectInput
	if (FAILED(DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&g_pDirectInput, NULL)))
	{
		UE_LOG(LogTemp, Error, TEXT("DirectInput initialization failed."));
		return;
	}

	// Enumerar os dispositivos de DirectInput
	if (FAILED(g_pDirectInput->CreateDevice(GUID_Joystick, &g_pGamepad, NULL)))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create DirectInput device."));
		return;
	}

	// Configurar o formato de dados para o dispositivo (gamepad)
	if (FAILED(g_pGamepad->SetDataFormat(&c_dfDIJoystick)))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to set data format for DirectInput device."));
		return;
	}

	// Configurar modo cooperativo
	if (FAILED(g_pGamepad->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to set cooperative level for DirectInput device."));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("DirectInput initialized successfully!"));
}
void AJogPlayerController::CheckControllerState()
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++) // Verificar até 4 controladores
	{
		
		if (XInputGetState(i, &state) == ERROR_SUCCESS)
		{
			UE_LOG(LogTemp, Error, TEXT("Controller %d is connected!"), XInputGetState(i, &state));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Controller %d is disconnected!"), XInputGetState(i, &state));
			//
		}
		
	}
	
}

void AJogPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Verificar o estado do controlador
	CheckControllerState();
	
}

AJogPlayerController::AJogPlayerController(): ForceFeedbackEffect(nullptr)
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

void AJogPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HWND hwnd = GetGameWindowHandle();

	if (hwnd)
	{
		// Inicializa DirectInput com o handle da janela
		InitializeDirectInput(hwnd);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get HWND for the game window."));
	}
	
	// Defina uma câmera fixa em um ponto específico
	bAutoManageActiveCameraTarget = true;

	if (!ForceFeedbackEffect)
	{
		ForceFeedbackEffect = LoadObject<UForceFeedbackEffect>(nullptr, TEXT("/Game/Input/ForceFeedback/BP_FeedbackPlayer.BP_FeedbackPlayer"));
	}
	
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
			FixedCamera->GetCameraComponent()->AspectRatio = ViewportSize.X / ViewportSize.Y;
		}
		
		// Definindo a câmera como a visão atual
		SetViewTarget(FixedCamera);
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		// Subsystem->ClearAllMappings();
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
		UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter not found"));
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("Canceled"));

	UMovementCharacterControlYawUseCase::Handle(PlayerCharacter->MovementPlayerCharacter, 0.0f);
}

void AJogPlayerController::ControllRotation(const FInputActionValue& InputController)
{
	float InputVector = InputController.Get<float>();

	UE_LOG(LogTemp, Error, TEXT("InputVector: %f"), InputVector);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (!PlayerCharacter)
	{
		return;
	}

	if (ForceFeedbackEffect)
	{
		UE_LOG(LogTemp, Error, TEXT("ForceFeedbackEffect: %s"), *ForceFeedbackEffect->GetName());
		// Jogar efeito de Force Feedback
		this->ClientPlayForceFeedback(ForceFeedbackEffect,FForceFeedbackParameters());
	}
	UMovementCharacterControlYawUseCase::Handle(PlayerCharacter->MovementPlayerCharacter, InputVector);
}

void AJogPlayerController::ControllRigth(const FInputActionValue& InputController)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (!PlayerCharacter)
	{
		return;
	}

	FVector InputVector = InputController.Get<FVector>();
	UE_LOG(LogTemp, Error, TEXT("InputVector: %s"), *InputVector.ToString());
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
