// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Interfaces/CharacterComponents/UpdateAttributesCharacterComponentInterface.h"
#include "NewProject/Interfaces/CharacterComponents/UpdateStateCharacterComponentInterface.h"
#include "UObject/Object.h"
#include "UpdateStateCharacterComponentUseCase.generated.h"

/**
 * 
 */
UCLASS()
class NEWPROJECT_API UUpdateStateCharacterComponentUseCase : public UObject
{
	GENERATED_BODY()

public:
	static void Handle(
		const TScriptInterface<IUpdateStateCharacterComponentInterface>& ComponentState,
		const TScriptInterface<IUpdateAttributesCharacterComponentInterface>& ComponentBaseAttributes
		);
};
