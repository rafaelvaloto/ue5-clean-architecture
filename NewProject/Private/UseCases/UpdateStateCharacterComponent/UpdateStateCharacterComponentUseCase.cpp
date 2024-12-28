// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/UpdateStateCharacterComponent/UpdateStateCharacterComponentUseCase.h"
#include "NewProject/Interfaces/CharacterComponents/UpdateAttributesCharacterComponentInterface.h"

void UUpdateStateCharacterComponentUseCase::Handle
(
	const TScriptInterface<IUpdateStateCharacterComponentInterface>& ComponentState,
	const TScriptInterface<IUpdateAttributesCharacterComponentInterface>& ComponentBaseAttributes
)
{
	const float VelocityCurrent = ComponentBaseAttributes->GetVelocitySize();
	
	if (
		VelocityCurrent > 0.0f &&
		VelocityCurrent <= 100.0f
	)
	{
		if (ComponentState->GetState() != EPlayerCharacterState::Walking)
		{
			ComponentState->SetCurrentState(EPlayerCharacterState::Walking);
		}
		return;
	}

	if (
		VelocityCurrent > 0.0f &&
		VelocityCurrent > 100.0f
	)
	{
		if (ComponentState->GetState() != EPlayerCharacterState::Running)
		{
			ComponentState->SetCurrentState(EPlayerCharacterState::Running);
		}
		return;
	}

	if (ComponentState->GetState() != EPlayerCharacterState::Idle)
	{
		ComponentState->SetCurrentState(EPlayerCharacterState::Idle);
	}
}
