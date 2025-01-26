// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NewProject/Interfaces/CharacterComponents/PlayAnimMontageComponentInterface.h"
#include "NewProject/Interfaces/CharacterComponents/SelectClosestBoneCharacterComponentInterface.h"
#include "NewProject/Interfaces/CharacterComponents/UpdateStateCharacterComponentInterface.h"
#include "NewProject/Interfaces/MotionMatchHelpersComponents/SelectorPoseSearchDatabaseInterface.h"
#include "ActionCharacterTackleSliderUseCase.generated.h"

/**
 * 
 */
UCLASS()
class NEWPROJECT_API UActionCharacterTackleSliderUseCase : public UObject
{
	GENERATED_BODY()

public:
	static void Handle(
		const TScriptInterface<ISelectClosestBoneCharacterComponentInterface>& SelectBoneComponent,
		const TScriptInterface<IPlayAnimMontageComponentInterface>& PlayAnimMontageComponent,
		const TScriptInterface<IUpdateStateCharacterComponentInterface>& StateCharacterComponent,
		const TScriptInterface<ISelectorPoseSearchDatabaseInterface>& SelectorPoseSearchDatabase,
		const bool bIsStarted
	);
};
