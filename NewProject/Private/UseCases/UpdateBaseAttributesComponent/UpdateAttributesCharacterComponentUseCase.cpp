// Fill out your copyright notice in the Description page of Project Settings.


#include "NewProject/Public/UseCases/UpdateAttributesCharacterComponent/UpdateAttributesCharacterComponentUseCase.h"

#include "Application/PlayerCharacter/PlayerCharacter.h"

void UUpdateAttributesCharacterComponentUseCase::Handle(
	const TScriptInterface<IUpdateAttributesCharacterComponentInterface>& Component,
	const APlayerCharacter* Actor
)
{
	const FVector Location = Actor->GetActorLocation();
	const FVector Velocity = Actor->GetVelocity();
	
	Component->SetVelocityCurrent(Velocity);
	Component->SetLocationCurrent(Location);
}
