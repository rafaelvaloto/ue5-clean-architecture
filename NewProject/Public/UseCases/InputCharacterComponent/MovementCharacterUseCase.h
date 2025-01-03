﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NewProject/Interfaces/CharacterComponents/InputCharacterInterface.h"
#include "MovementCharacterUseCase.generated.h"

/**
 * 
 */
UCLASS()
class NEWPROJECT_API UMovementCharacterUseCase : public UObject
{
	GENERATED_BODY()

public:
	static void Handle(const TScriptInterface<IInputCharacterInterface>& MovementComponent, const FVector& InputController);
};
