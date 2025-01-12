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
	const float AccelerationCurrent = ComponentBaseAttributes->GetMagnitudeAcceleration();
	
	if (
		VelocityCurrent > 0.01f &&
		VelocityCurrent < 30.0f &&
		AccelerationCurrent < 100.f
	)
	{
		UE_LOG(LogTemp, Error, TEXT("Velocity: %f"), VelocityCurrent);
		if (ComponentState->GetState() != EPlayerCharacterStateEnum::Walking)
		{
			ComponentState->SetCurrentState(EPlayerCharacterStateEnum::Walking);
		}
		
		if (ComponentState->GetState() != EPlayerCharacterStateEnum::WalkingPivot && IsDirectionChange)
		{
			ComponentState->SetCurrentState(EPlayerCharacterStateEnum::WalkingPivot);
		}
		return;
	}

	if (
		VelocityCurrent > 30.0f ||
		AccelerationCurrent > 100.f
	)
	{
		if (ComponentState->GetState() != EPlayerCharacterStateEnum::Running)
		{
			ComponentState->SetCurrentState(EPlayerCharacterStateEnum::Running);
		}
		
		if (ComponentState->GetState() != EPlayerCharacterStateEnum::RunningPivot && IsDirectionChange)
		{
			ComponentState->SetCurrentState(EPlayerCharacterStateEnum::RunningPivot);
			return;
		}

		if (AccelerationCurrent > 0.0f || VelocityCurrent > 0.0f)
		{
			UE_LOG(LogTemp, Error, TEXT("AccelerationCurrent: %f"), AccelerationCurrent);
			UE_LOG(LogTemp, Error, TEXT("VelocityCurrent: %f"), VelocityCurrent);	
		}
		
		return;
	}

	if (ComponentState->GetState() != EPlayerCharacterStateEnum::Idle)
	{
		ComponentState->SetCurrentState(EPlayerCharacterStateEnum::Idle);
	}
}
