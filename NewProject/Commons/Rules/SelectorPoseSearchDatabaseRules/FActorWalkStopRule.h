// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Interfaces/Helpers/RuleBase.h"

/**
 * 
 */
class NEWPROJECT_API FActorWalkStopRule : public IRuleBase
{
	float MaxSpeedThreshold;

public:
	FActorWalkStopRule
	(
		float MaxSpeedThreshold = 20.0f
	): MaxSpeedThreshold(MaxSpeedThreshold) {}

	virtual ~FActorWalkStopRule() override
	{
		UE_LOG(LogTemp, Warning, TEXT("FActorWalkStopRule destrutor chamado - %p"), this);
	}

	virtual bool Validate(const UObject* Target) const override
	{
		const APlayerCharacter* Actor = Cast<APlayerCharacter>(Target);

		if (const bool IsValid = Actor->UpdatedBaseAttributesComponent->GetVelocitySize() <= MaxSpeedThreshold; !IsValid)
		{
			UE_LOG(LogTemp, Warning, TEXT("FActorWalkStopRule::Validate - %s"), *GetRuleName());
			return false;
		}

		UE_LOG(LogTemp, Warning, TEXT("FActorWalkStopRule::Validate - %s"), *GetRuleName());
		return true;
	}
	

	virtual FString GetRuleName() const override
	{
		return FString::Printf(TEXT("FActorWalkStopRule"));
	}

private:
	// Método fictício para obter o "DeltaTime" (ou seja, o intervalo de tempo entre cálculos)
	float GetDeltaTime() const
	{
		return FApp::GetDeltaTime(); // Ou use seu sistema de temporização
	}
};
