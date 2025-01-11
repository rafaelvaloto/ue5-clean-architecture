// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/UpdateStateCharacterComponent/UpdateStateCharacterComponentUseCase.h"

#include "Components/Character/UpdateStateCharacterComponent.h"
#include "NewProject/Interfaces/CharacterComponents/UpdateAttributesCharacterComponentInterface.h"

void UUpdateStateCharacterComponentUseCase::Handle
(
	const TScriptInterface<IUpdateStateCharacterComponentInterface>& ComponentState,
	const TScriptInterface<IUpdateAttributesCharacterComponentInterface>& ComponentBaseAttributes
)
{
	const bool IsDirectionChange = ComponentBaseAttributes->IsDetectedDirectionChange();
	const float VelocityCurrent = ComponentBaseAttributes->GetVelocitySize();
	if (
		VelocityCurrent > 0.01f &&
		VelocityCurrent < 100.0f
	)
	{
		if (ComponentState->GetState() != EPlayerCharacterStateEnum::WalkingPivot && IsDirectionChange)
		{
			ComponentState->SetCurrentState(EPlayerCharacterStateEnum::WalkingPivot);
			if (GEngine)
			{
				EPlayerCharacterStateEnum State = ComponentState->GetState();
				FText val = UUpdateStateCharacterComponent::GetStateDisplayName(State);
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, val.ToString());
			}
			return;
		}
		
		UE_LOG(LogTemp, Error, TEXT("Velocity: %f"), VelocityCurrent);
		if (ComponentState->GetState() != EPlayerCharacterStateEnum::Walking)
		{
			ComponentState->SetCurrentState(EPlayerCharacterStateEnum::Walking);
		}
		return;
	}

	if (
		VelocityCurrent > 100.0f
	)
	{
		if (ComponentState->GetState() != EPlayerCharacterStateEnum::RunningPivot && IsDirectionChange)
		{
			ComponentState->SetCurrentState(EPlayerCharacterStateEnum::RunningPivot);
			if (GEngine)
			{
				EPlayerCharacterStateEnum State = ComponentState->GetState();
				FText val = UUpdateStateCharacterComponent::GetStateDisplayName(State);
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, val.ToString());
			}
			return;
		}
		
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
