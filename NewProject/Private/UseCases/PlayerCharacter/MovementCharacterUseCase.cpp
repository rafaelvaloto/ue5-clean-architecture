// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/PlayerCharacter/MovementCharacterUseCase.h"
#include "Components/PlayerCharacter/MovementCharacterComponent.h"

UMovementCharacterUseCase::UMovementCharacterUseCase()
{
	// Default values
}

void UMovementCharacterUseCase::HandleCharacterMovement(TScriptInterface<IMovementCharacterInterface> MovementComponent, FVector InputController)
{
	// Chama o component e aplica movimentação ao Character
	MovementComponent->Move(InputController);

	// Implementar Aqui Outras lógicas para esse UseCase...
}