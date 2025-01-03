// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Character/UpdateTrajectoryCharacterComponent.h"

UUpdateTrajectoryCharacterComponent::UUpdateTrajectoryCharacterComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) // Chamando o construtor da base
{
	// Inicializar variáveis específicas da classe derivada, se necessário.

	
}

void UUpdateTrajectoryCharacterComponent::OnMovementUpdated(float DeltaSeconds, FVector OldLocation, FVector OldVelocity)
{
	
}
