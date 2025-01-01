// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Interfaces/Helpers/RuleBase.h"

/**
 * 
 */
class NEWPROJECT_API FActorIdleRule final : public IRuleBase
{
	float MaxSpeedThreshold;
public:
	FActorIdleRule(
		float MaxSpeedThreshold = 0.0f
	): MaxSpeedThreshold(MaxSpeedThreshold) {};


	virtual bool Validate(const UObject* Target) const override
	{
		const AActor* Actor = Cast<AActor>(Target);
		if (!Actor) return false;

		FVector Velocity = Actor->GetVelocity();
		float Speed = Velocity.Size();

		FVector PrevVelocity = GetPreviousVelocity(Actor);
		FVector Acceleration = (Velocity - PrevVelocity) / GetDeltaTime();
		float AccelMagnitude = Acceleration.Size();

		return (Speed <= MaxSpeedThreshold);
	}

private:
	// Método fictício para obter a velocidade anterior (você pode implementar isso com um sistema mais robusto)
	FVector GetPreviousVelocity(const AActor* Actor) const
	{
		// Exemplo: Obtenha isso de um sistema de rastreamento ou buffer dentro de um componente customizado.
		// Placeholder
		return FVector::ZeroVector;
	}

	// Método fictício para obter o "DeltaTime" (ou seja, o intervalo de tempo entre cálculos)
	float GetDeltaTime() const
	{
		return FApp::GetDeltaTime(); // Ou use seu sistema de temporização
	}
	
};
