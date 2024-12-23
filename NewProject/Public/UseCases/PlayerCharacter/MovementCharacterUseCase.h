﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NewProject/Interfaces/PlayerCharacter/MovementCharacterInterface.h"
#include "MovementCharacterUseCase.generated.h"

/**
 * 
 */
UCLASS()
class NEWPROJECT_API UMovementCharacterUseCase : public UObject
{
	GENERATED_BODY()

public:
	UMovementCharacterUseCase();

	static void HandleCharacterMovement(TScriptInterface<IMovementCharacterInterface> MovementComponent, FVector InputController);
};
