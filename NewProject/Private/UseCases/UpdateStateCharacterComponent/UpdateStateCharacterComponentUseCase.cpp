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
	const float VelocityCurrent = ComponentBaseAttributes->GetVelocitySize();
	const bool IsDirectionChange = ComponentBaseAttributes->IsDetectedDirectionChange();
	const float AccelerationCurrent = ComponentBaseAttributes->GetMagnitudeAcceleration();

	if (
		ComponentState->GetState() == EPlayerCharacterStateEnum::Interval ||
		ComponentState->GetState() == EPlayerCharacterStateEnum::Tackle ||
		ComponentState->GetState() == EPlayerCharacterStateEnum::TackleSlider ||
		ComponentState->GetState() == EPlayerCharacterStateEnum::Controlling ||
		ComponentState->GetState() == EPlayerCharacterStateEnum::ControllingTrajectoryChange
	)
	{
		return;
	}

	if (
		VelocityCurrent >= 30.0f ||
		AccelerationCurrent > 100.f
	)
	{
		if (ComponentState->GetState() != EPlayerCharacterStateEnum::RunningPivot && IsDirectionChange)
		{
			ComponentState->SetCurrentState(EPlayerCharacterStateEnum::RunningPivot);
			return;
		}

		if (ComponentState->GetState() != EPlayerCharacterStateEnum::Running)
		{
			ComponentState->SetCurrentState(EPlayerCharacterStateEnum::Running);
			return;
		}
	}

	if (
		VelocityCurrent > 0.01f &&
		VelocityCurrent < 30.0f
	)
	{
		if (
			ComponentState->GetState() != EPlayerCharacterStateEnum::WalkingPivot
			&& IsDirectionChange
		)
		{
			ComponentState->SetCurrentState(EPlayerCharacterStateEnum::WalkingPivot);
			return;
		}

		if (
			ComponentState->GetState() != EPlayerCharacterStateEnum::Walking
		)
		{
			ComponentState->SetCurrentState(EPlayerCharacterStateEnum::Walking);
			return;
		}
	}

	if (ComponentState->GetState() != EPlayerCharacterStateEnum::Idle)
	{
		ComponentState->SetCurrentState(EPlayerCharacterStateEnum::Idle);
	}
}
