// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Application/PlayerCharacter/PlayerCharacter.h"
#include "NewProject/Interfaces/Helpers/RuleBase.h"

/**
 * 
 */
class NEWPROJECT_API FActorWalkPivotsRule final : public IRuleBase
{
	const float MaxSpeedThreshold;
	const float MinSpeedThreshold;

public:
	explicit FActorWalkPivotsRule(
		const float MinSpeedThreshold = 0.0f,
		const float MaxSpeedThreshold = 100.0f
	): MaxSpeedThreshold(MaxSpeedThreshold), MinSpeedThreshold(MinSpeedThreshold) {}

	virtual ~FActorWalkPivotsRule() override
	{
		UE_LOG(LogTemp, Warning, TEXT("FActorWalkPivotsRule destrutor chamado - %p"), this);
	}
	
	virtual bool Validate(const UObject* Target) const override
	{
		const APlayerCharacter* Actor = Cast<APlayerCharacter>(Target);
		if (!Actor) return false;

		const float Speed = Actor->UpdatedBaseAttributesComponent->GetVelocitySize();
		if (Speed < MinSpeedThreshold || Speed > MaxSpeedThreshold) return false;
		
		return true;
	}
	
	virtual FString GetRuleName() const override
	{
		return FString::Printf(TEXT("FActorWalkPivotsRule"));
	}
};
