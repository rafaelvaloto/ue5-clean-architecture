// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NewProject/Interfaces/CharacterComponents/UpdateAttributesCharacterComponentInterface.h"
#include "NewProject/Interfaces/CharacterComponents/UpdateStateCharacterComponentInterface.h"
#include "CharacterChangeDirectionControllBallUseCase.generated.h"

/**
 * 
 */
UCLASS()
class NEWPROJECT_API UCharacterChangeDirectionControllBallUseCase : public UObject
{
	GENERATED_BODY()

public:
	static void Handle(
		const TScriptInterface<IUpdateAttributesCharacterComponentInterface>& UpdateAttributes,
		const TScriptInterface<IUpdateStateCharacterComponentInterface>& StateCharacterComponent
	);
};
