// Fill out your copyright notice in the Description page of Project Settings.


#include "NewProject/Public/UseCases/InputCharacterComponent/MovementCharacterUseCase.h"
#include "Components/Character/InputCharacterComponent.h"

UMovementCharacterUseCase::UMovementCharacterUseCase()
{
	// Default values
}

void UMovementCharacterUseCase::HandleCharacterMovement(TScriptInterface<IInputCharacterInterface> MovementComponent, FVector InputController)
{
	// Chama o component e aplica movimentação ao Character
	MovementComponent->Move(InputController);

	// Implementar Aqui Outras lógicas para esse UseCase...
}