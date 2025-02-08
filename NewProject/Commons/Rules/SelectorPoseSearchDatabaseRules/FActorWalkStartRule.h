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
		const float MaxAccelerationThreshold = 50.0f, const float MaxSpeedThreshold = 15.0f
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

		if (AccelMagnitude > MaxAccelerationThreshold && Speed > MaxSpeedThreshold)
		{
			return false;
		}
		
		return true;
	}
	

	virtual FString GetRuleName() const override
	{
		return FString::Printf(TEXT("FActorWalkStartRule"));
	}
};
