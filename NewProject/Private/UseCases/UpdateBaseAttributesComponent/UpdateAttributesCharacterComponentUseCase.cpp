// Fill out your copyright notice in the Description page of Project Settings.


#include "NewProject/Public/UseCases/UpdateAttributesCharacterComponent/UpdateAttributesCharacterComponentUseCase.h"

void UUpdateAttributesCharacterComponentUseCase::Handle(
	const TScriptInterface<IUpdateAttributesCharacterComponentInterface>& Component,
	const AActor* Actor
)
{
	Component->SetVelocityCurrent(Actor->GetVelocity());
}
