// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Interfaces/CharacterComponents/InputCharacterInterface.h"
#include "NewProject/Interfaces/CharacterComponents/UpdateStateCharacterComponentInterface.h"
#include "UObject/Object.h"
#include "MovementCharacterControlYawUseCase.generated.h"

/**
 * 
 */
UCLASS()
class NEWPROJECT_API UMovementCharacterControlYawUseCase : public UObject
{
	GENERATED_BODY()

public:
	static void Handle(
		const TScriptInterface<IInputCharacterInterface>& MovementComponent,
		const TScriptInterface<IUpdateStateCharacterComponentInterface>& StateComponent,
		const float InputValue
	);
};
