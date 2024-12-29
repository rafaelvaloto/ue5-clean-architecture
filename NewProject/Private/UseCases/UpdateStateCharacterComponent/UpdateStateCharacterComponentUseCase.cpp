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
		VelocityCurrent < 201.0f
	)
	{
		if (ComponentState->GetState() != EPlayerCharacterStateEnum::Walking)
		{
			ComponentState->SetCurrentState(EPlayerCharacterStateEnum::Walking);
		}
		return;
	}

	if (
		VelocityCurrent > 200.0f
	)
	{
		if (ComponentState->GetState() != EPlayerCharacterStateEnum::Running)
		{
			ComponentState->SetCurrentState(EPlayerCharacterStateEnum::Running);
		}
		return;
	}

	if (ComponentState->GetState() != EPlayerCharacterStateEnum::Idle)
	{
		ComponentState->SetCurrentState(EPlayerCharacterStateEnum::Idle);
	}
}
