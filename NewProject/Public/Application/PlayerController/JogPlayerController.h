﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "JogPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class NEWPROJECT_API AJogPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AJogPlayerController();

	virtual void SetDisableHaptics(bool bNewDisabled) override;

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void Move(const FInputActionValue& InputController);
	void ControllRigth(const FInputActionValue& InputController);
	void ControllRotation(const FInputActionValue& InputController);
	void ControllRotationCanceled(const FInputActionValue& InputController);
	void Tackle(const FInputActionValue& InputController);
	void TackleSlider(const FInputActionValue& InputController);
	void SetupDevice();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Deafult Mapping Context")
	UInputMappingContext* IMC_Default;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions")
	UInputAction* IA_Move;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions")
	UInputAction* IA_ControlRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions")
	UInputAction* IA_Tackle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions")
	UInputAction* IA_TackleSlider;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions")
	UInputAction* IA_ControllRigth;
};
