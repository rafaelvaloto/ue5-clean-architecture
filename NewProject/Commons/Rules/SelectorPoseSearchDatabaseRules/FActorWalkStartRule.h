﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Interfaces/Helpers/RuleBase.h"

/**
 * 
 */
class NEWPROJECT_API FActorWalkStartRule final : public IRuleBase
{
	float MinAccelerationThreshold;  // Limite mínimo de aceleração
	float MaxAccelerationThreshold;  // Limite máximo de aceleração
	float MinSpeedThreshold;
	float MaxSpeedThreshold;

public:
	FActorWalkStartRule
	(
		float MinAccelerationThreshold = 5.0f, float MaxAccelerationThreshold = 15.0f, float MinSpeedThreshold = 5.0,  float MaxSpeedThreshold = 15.0
	): MinAccelerationThreshold(MinAccelerationThreshold), MaxAccelerationThreshold(MaxAccelerationThreshold), MinSpeedThreshold(MinSpeedThreshold), MaxSpeedThreshold(MaxSpeedThreshold) {}

	virtual bool Validate(const UObject* Target) const override
	{
		const AActor* Actor = Cast<AActor>(Target);
		if (!Actor) return false;

		FVector Velocity = Actor->GetVelocity();
		float Speed = Velocity.Size();

		FVector PrevVelocity = GetPreviousVelocity(Actor);
		FVector Acceleration = (Velocity - PrevVelocity) / GetDeltaTime();
		float AccelMagnitude = Acceleration.Size();

		bool IsAccelInRange = (AccelMagnitude >= MinAccelerationThreshold && AccelMagnitude <= MaxAccelerationThreshold);
		bool IsSpeedValid = Speed >= MinSpeedThreshold && Speed <= MaxSpeedThreshold;

		return IsAccelInRange && IsSpeedValid;
	}

	virtual FString GetRuleName() const override
	{
		return FString::Printf(TEXT("FActorWalkStartRule"));
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
