// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Application/PlayerCharacter/PlayerCharacter.h"
#include "NewProject/Interfaces/Helpers/RuleBase.h"

/**
 * 
 */
class NEWPROJECT_API FActorWalkStartRule : public IRuleBase
{
	float MaxAccelerationThreshold;
	float MaxSpeedThreshold;

public:
	explicit FActorWalkStartRule
	(
		const float MaxAccelerationThreshold = 600.0f, const float MaxSpeedThreshold = 5.0f
	): MaxAccelerationThreshold(MaxAccelerationThreshold), MaxSpeedThreshold(MaxSpeedThreshold) {}

	virtual ~FActorWalkStartRule() override
	{
		UE_LOG(LogTemp, Warning, TEXT("FActorWalkStartRule destrutor chamado - %p"), this);
	}

	virtual bool Validate(const UObject* Target) const override
	{
		const APlayerCharacter* Actor = Cast<APlayerCharacter>(Target);
		if (!Actor) return false;

		const float Speed = Actor->UpdatedBaseAttributesComponent->GetVelocitySize();
		const float AccelMagnitude = Actor->UpdatedBaseAttributesComponent->GetMagnitudeAcceleration();

		if (const bool IsValid = AccelMagnitude <= MaxAccelerationThreshold && Speed <= MaxSpeedThreshold; !IsValid)
		{
			UE_LOG(LogTemp, Error, TEXT("FActorWalkStartRule Invalid %s"), *GetRuleName());
			return false;
		}

		UE_LOG(LogTemp, Error, TEXT("FActorWalkStartRule Valid %s"), *GetRuleName());
		return true;
	}
	

	virtual FString GetRuleName() const override
	{
		return FString::Printf(TEXT("FActorWalkStartRule"));
	}
};
