﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Application/PlayerCharacter/PlayerCharacter.h"
#include "NewProject/Interfaces/Helpers/RuleBase.h"

/**
 * 
 */
class NEWPROJECT_API FActorWalkStopRule : public IRuleBase
{
	float MaxSpeedThreshold;

public:
	explicit FActorWalkStopRule
	(
		const float MaxSpeedThreshold = 5.0f
	): MaxSpeedThreshold(MaxSpeedThreshold) {}

	virtual ~FActorWalkStopRule() override
	{
		UE_LOG(LogTemp, Warning, TEXT("FActorWalkStopRule destrutor chamado - %p"), this);
	}

	virtual bool Validate(const UObject* Target) const override
	{
		const APlayerCharacter* Actor = Cast<APlayerCharacter>(Target);

		if (Actor->UpdatedBaseAttributesComponent->GetVelocitySize() <= MaxSpeedThreshold)
		{
			return true;
		}
		
		return false;
	}
	

	virtual FString GetRuleName() const override
	{
		return FString::Printf(TEXT("FActorWalkStopRule"));
	}
};
