// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NewProject/Enums/CharacterStates/PlayerCharacterStateEnum.h"
#include "NewProject/Interfaces/MotionMatchHelpersComponents/SelectorPoseSearchDatabaseInterface.h"
#include "UpdatePoseSearchDatabaseWithStateUseCase.generated.h"


/**
 * 
 */
UCLASS()
class NEWPROJECT_API UUpdatePoseSearchDatabaseWithStateUseCase : public UObject
{
	GENERATED_BODY()

public:
	static bool Handle
	(
		const TScriptInterface<ISelectorPoseSearchDatabaseInterface>& Component,
		EPlayerCharacterStateEnum CurrentState,
		EPlayerCharacterStateEnum PreviousState
	);
};


