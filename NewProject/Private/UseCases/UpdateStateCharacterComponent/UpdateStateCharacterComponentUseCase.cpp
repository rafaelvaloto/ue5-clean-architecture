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
		VelocityCurrent > 0.001f &&
		VelocityCurrent < 201.0f
	)
	{
		UE_LOG(LogTemp, Error, TEXT("Velocity: %f"), VelocityCurrent);
		if (ComponentState->GetState() != EPlayerCharacterStateEnum::Walking)
		{
			ComponentState->SetCurrentState(EPlayerCharacterStateEnum::Walking);
		}
		return;
	}

	if (
		VelocityCurrent > 600.0f
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
