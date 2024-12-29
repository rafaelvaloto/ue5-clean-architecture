// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/CharacterTrajectoryComponent/CharacterTrajectoryComponentUseCase.h"
#include "NewProject/Interfaces/CharacterComponents/UpdateAttributesCharacterComponentInterface.h"


void UCharacterTrajectoryComponentUseCase::Handle
(
	const TScriptInterface<IUpdateTrajectoryCharacterComponentInterface>& Component,
	const TScriptInterface<IUpdateAttributesCharacterComponentInterface>& ComponentAttr,
	const float DeltaTime
)
{
	Component->OnMovementUpdated(DeltaTime, ComponentAttr->GetLocationCurrent(), ComponentAttr->GetVelocityCurrent());
}
