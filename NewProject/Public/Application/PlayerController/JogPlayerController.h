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

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void Move(const FInputActionValue& InputController);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Deafult Mapping Context")
	UInputMappingContext* IMC_Default;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions")
	UInputAction* IA_Move;
};