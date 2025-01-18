// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Application/PlayerCharacter/PlayerCharacter.h"
#include "UObject/Object.h"
#include "ActionCHaracterTackleSliderUseCase.generated.h"

/**
 * 
 */
UCLASS()
class NEWPROJECT_API UActionCHaracterTackleSliderUseCase : public UObject
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
