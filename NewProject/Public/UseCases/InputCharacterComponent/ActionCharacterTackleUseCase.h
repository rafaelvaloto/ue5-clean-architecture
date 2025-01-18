// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Application/PlayerCharacter/PlayerCharacter.h"
#include "NewProject/Interfaces/CharacterComponents/InputCharacterInterface.h"
#include "NewProject/Interfaces/CharacterComponents/UpdateStateCharacterComponentInterface.h"
#include "NewProject/Interfaces/MotionMatchHelpersComponents/SelectorPoseSearchDatabaseInterface.h"
#include "UObject/Object.h"
#include "ActionCharacterTackleUseCase.generated.h"

/**
 * 
 */
UCLASS()
class NEWPROJECT_API UActionCharacterTackleUseCase : public UObject
{
	GENERATED_BODY()
public:
	static void Handle(
		APlayerCharacter* Character,
		const TScriptInterface<IInputCharacterInterface>& MovementComponent,
		const TScriptInterface<IUpdateStateCharacterComponentInterface>& StateCharacterComponent,
		const TScriptInterface<ISelectorPoseSearchDatabaseInterface>& SelectorPoseSearchDatabase,
		const bool bIsStarted
	);
	
};
