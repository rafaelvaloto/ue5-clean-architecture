// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Application/PlayerCharacter/PlayerCharacter.h"
#include "NewProject/Interfaces/Helpers/RuleBase.h"


/**
 * 
 */
class NEWPROJECT_API FActorIdleRule final : public IRuleBase
{
	float MaxSpeedThreshold;
	
public:
	explicit FActorIdleRule(
		const float MaxSpeedThreshold = 0.01f
	): MaxSpeedThreshold(MaxSpeedThreshold) {}

	virtual ~FActorIdleRule() override
	{
		UE_LOG(LogTemp, Warning, TEXT("FActorIdleRule destrutor chamado - %p"), this);
	}

	virtual bool Validate(const UObject* Target) const override
	{
		const APlayerCharacter* Actor = Cast<APlayerCharacter>(Target);
		return Actor->UpdatedBaseAttributesComponent->GetVelocitySize() <= MaxSpeedThreshold;
	}
	
	virtual FString GetRuleName() const override
	{
		return FString::Printf(TEXT("FActorIdle"));
	}
};
