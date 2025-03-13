// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NewProject/Interfaces/CharacterComponents/PlayAnimMontageComponentInterface.h"
#include "NewProject/Interfaces/CharacterComponents/SelectClosestBoneCharacterComponentInterface.h"
#include "NewProject/Interfaces/CharacterComponents/SweepByChannelComponentInterface.h"
#include "NewProject/Interfaces/CharacterComponents/UpdateStateCharacterComponentInterface.h"
#include "NewProject/Interfaces/MotionMatchHelpersComponents/SelectorPoseSearchDatabaseInterface.h"
#include "CharacterControllBallUseCase.generated.h"

/**
 * 
 */
UCLASS()
class NEWPROJECT_API UCharacterControllBallUseCase : public UObject
{
	GENERATED_BODY()

public:
	static void Handle(
		const TScriptInterface<ISweepByChannelComponentInterface>& SweepChannel,
		const TScriptInterface<ISelectClosestBoneCharacterComponentInterface>& SelectBoneComponent,
		const TScriptInterface<IUpdateStateCharacterComponentInterface>& StateCharacterComponent,
		const TScriptInterface<IPlayAnimMontageComponentInterface>& PlayAnimMontageComponent,
		const TScriptInterface<ISelectorPoseSearchDatabaseInterface>& SelectorPoseSearchDatabase
	);
};
