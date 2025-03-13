// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/InputCharacterComponent/MovementCharacterControlYawUseCase.h"

#include "NewProject/Interfaces/CharacterComponents/UpdateStateCharacterComponentInterface.h"

void UMovementCharacterControlYawUseCase::Handle(
	const TScriptInterface<IInputCharacterInterface>& MovementComponent,
	const TScriptInterface<IUpdateStateCharacterComponentInterface>& StateComponent,
	const float InputValue
)
{
	if (
		(
			StateComponent->GetState() != EPlayerCharacterStateEnum::Controlling &&
			StateComponent->GetState() != EPlayerCharacterStateEnum::ControllingTrajectoryChange
		) ||
		InputValue == 0.0f
	)
	{
		MovementComponent->ControlYaw(InputValue);
	}
}
