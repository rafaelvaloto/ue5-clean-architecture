// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Application/PlayerCharacter/PlayerCharacter.h"
#include "NewProject/Interfaces/Helpers/RuleBase.h"

/**
 * 
 */
class NEWPROJECT_API FActorRunPivotsRule final : public IRuleBase
{
	const float MaxSpeedThreshold;
	const float MinAccelerationThreshold;

public:
	explicit FActorRunPivotsRule(
		const float MaxSpeedThreshold = 500.0f,
		const float MinAccelerationThreshold = 49.0f
	): MaxSpeedThreshold(MaxSpeedThreshold), MinAccelerationThreshold(MinAccelerationThreshold)
	{
	}

	virtual ~FActorRunPivotsRule() override
	{
		UE_LOG(LogTemp, Warning, TEXT("FActorRunPivotsRule destrutor chamado - %p"), this);
	}

	virtual bool Validate(const UObject* Target) const override
	{
		const APlayerCharacter* Actor = Cast<APlayerCharacter>(Target);
		if (!Actor) return false;

		const float Speed = Actor->UpdatedBaseAttributesComponent->GetVelocitySize();
		const float Acceleration = Actor->UpdatedBaseAttributesComponent->GetMagnitudeAcceleration();
		const float isDetectDirectChange = Actor->UpdatedBaseAttributesComponent->IsDetectedDirectionChange();
		if (
			Acceleration >= MinAccelerationThreshold && Speed <= MaxSpeedThreshold ||
			isDetectDirectChange
		)
		{
			return true;
		}

		return false;
	}

	virtual FString GetRuleName() const override
	{
		return FString::Printf(TEXT("FActorRunPivotsRule"));
	}
};
