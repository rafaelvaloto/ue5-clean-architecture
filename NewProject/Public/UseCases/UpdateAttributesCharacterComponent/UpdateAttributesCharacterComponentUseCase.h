// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Application/PlayerCharacter/PlayerCharacter.h"
#include "NewProject/Interfaces/CharacterComponents/UpdateAttributesCharacterComponentInterface.h"
#include "UObject/Object.h"
#include "UpdateAttributesCharacterComponentUseCase.generated.h"

/**
 * 
 */
UCLASS()
class NEWPROJECT_API UUpdateAttributesCharacterComponentUseCase : public UObject
{
	GENERATED_BODY()

public:
	static void Handle(const TScriptInterface<IUpdateAttributesCharacterComponentInterface>& Component, const APlayerCharacter* Actor);
};
