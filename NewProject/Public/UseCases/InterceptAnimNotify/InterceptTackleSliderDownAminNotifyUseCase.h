// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Interfaces/CharacterComponents/InputCharacterInterface.h"
#include "NewProject/Interfaces/CharacterComponents/PlayAnimMontageComponentInterface.h"
#include "NewProject/Interfaces/CharacterComponents/UpdateAttributesCharacterComponentInterface.h"
#include "NewProject/Interfaces/CharacterComponents/UpdateStateCharacterComponentInterface.h"
#include "NewProject/Interfaces/MotionMatchHelpersComponents/SelectorPoseSearchDatabaseInterface.h"
#include "NewProject/Interfaces/StaticMeshActorComponents/CurrentBallComponentInterface.h"
#include "UObject/Object.h"
#include "InterceptTackleSliderDownAminNotifyUseCase.generated.h"

/**
 * 
 */
UCLASS()
class NEWPROJECT_API UInterceptTackleSliderDownAminNotifyUseCase : public UObject
{
	GENERATED_BODY()

public:
	static void Handle(
		TScriptInterface<IPlayAnimMontageComponentInterface> PlayAnimMontageComponent,
		TScriptInterface<IInputCharacterInterface> InputCharacterComponent,
		TScriptInterface<IUpdateStateCharacterComponentInterface> StateCharacterComponent,
		TScriptInterface<IUpdateAttributesCharacterComponentInterface> AttributesCharacterComponent,
		TScriptInterface<ISelectorPoseSearchDatabaseInterface> SelectorPoseSearchDatabase
	);
};
