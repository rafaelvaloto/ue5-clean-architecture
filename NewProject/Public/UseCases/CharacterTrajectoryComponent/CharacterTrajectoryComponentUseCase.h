// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Interfaces/CharacterComponents/UpdateAttributesCharacterComponentInterface.h"
#include "NewProject/Interfaces/CharacterComponents/UpdateTrajectoryCharacterComponentInterface.h"
#include "UObject/Object.h"
#include "CharacterTrajectoryComponentUseCase.generated.h"

/**
 * 
 */
UCLASS()
class NEWPROJECT_API UCharacterTrajectoryComponentUseCase : public UObject
{
	GENERATED_BODY()

public:
	static void Handle(
		const TScriptInterface<IUpdateTrajectoryCharacterComponentInterface>& Component,
		const TScriptInterface<IUpdateAttributesCharacterComponentInterface>& ComponentAttr,
		float DeltaTime
	);
};
