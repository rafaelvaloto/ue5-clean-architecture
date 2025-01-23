// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/InputCharacterComponent/MovementCharacterControlYawUseCase.h"

void UMovementCharacterControlYawUseCase::Handle(
	const TScriptInterface<IInputCharacterInterface>& MovementComponent,
	const float InputValue
)
{
	MovementComponent->ControlYaw(InputValue);
}
