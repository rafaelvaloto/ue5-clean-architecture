﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Character/UpdateStateCharacterComponent.h"
#include "NewProject/Enums/CharacterStates/PlayerCharacterStateEnum.h"
#include "NewProject/Interfaces/MotionMatchHelpersComponents/SelectorPoseSearchDatabaseInterface.h"
#include "UObject/Object.h"
#include "UpdateNodePoseSearchDatabaseUseCase.generated.h"


/**
 * 
 */
UCLASS()
class NEWPROJECT_API UUpdateNodePoseSearchDatabaseUseCase : public UObject
{
	GENERATED_BODY()

public:
	static void Handle
	(
		const TScriptInterface<ISelectorPoseSearchDatabaseInterface>& Component,
		EPlayerCharacterStateEnum CurrentState,
		EPlayerCharacterStateEnum PreviousState
	);
};


