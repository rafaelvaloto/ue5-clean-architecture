// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Application/PlayerCharacter/PlayerCharacter.h"
#include "NewProject/Interfaces/Helpers/RuleBase.h"

/**
 * 
 */
class NEWPROJECT_API FActorWalkStartRule final : public IRuleBase
{
	float MaxAccelerationThreshold;
	float MaxSpeedThreshold;

public:
	FActorWalkStartRule
	(
		const float MaxAccelerationThreshold = 50.0f, const float MaxSpeedThreshold = 30.f
	): MaxAccelerationThreshold(MaxAccelerationThreshold), MaxSpeedThreshold(MaxSpeedThreshold) {}

	virtual ~FActorWalkStartRule() override
	{
		UE_LOG(LogTemp, Warning, TEXT("FActorWalkStartRule destrutor chamado - %p"), this);
	}
	
	virtual bool Validate(const UObject* Target) const override
	{
		const APlayerCharacter* Actor = Cast<APlayerCharacter>(Target);
		if (!Actor) return false;

		const float DeltaTime = GetDeltaTime();
		
		const float Speed = Actor->UpdatedBaseAttributesComponent->GetVelocitySize();
		const FVector PrevVelocity = Actor->UpdatedBaseAttributesComponent->GetPreviousVelocity();
		const FVector CurrentVelocity = Actor->GetVelocity();

		const float AccelMagnitude = (CurrentVelocity - PrevVelocity).Size() / DeltaTime;

		if (const bool IsValid = AccelMagnitude <= MaxAccelerationThreshold && Speed <= MaxSpeedThreshold; !IsValid)
		{
			UE_LOG(LogTemp, Error, TEXT("FActorWalkStartRule Invalid %s"), *GetRuleName()); // ( Adicione uma mensagem de log aqui
			return false;
		}

		UE_LOG(LogTemp, Error, TEXT("FActorWalkStartRule Valid %s"), *GetRuleName()); // ( Adicione uma mensagem de log aqui
		return true;
	}
	

	virtual FString GetRuleName() const override
	{
		return FString::Printf(TEXT("FActorWalkStartRule"));
	}

private:
	// Método fictício para obter o "DeltaTime" (ou seja, o intervalo de tempo entre cálculos)
	float GetDeltaTime() const
	{
		return FApp::GetDeltaTime(); // Ou use seu sistema de temporização
	}
};
