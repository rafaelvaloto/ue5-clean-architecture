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
	const float MinSpeedThreshold;
	
public:
	explicit FActorRunPivotsRule(
		const float MaxSpeedThreshold = 300.0f,
		const float MinSpeedThreshold = 30.0f
	): MaxSpeedThreshold(MaxSpeedThreshold), MinSpeedThreshold(MinSpeedThreshold) {}

	virtual ~FActorRunPivotsRule() override
	{
		UE_LOG(LogTemp, Warning, TEXT("FActorRunPivotsRule destrutor chamado - %p"), this);
	}

	virtual bool Validate(const UObject* Target) const override
	{
		const APlayerCharacter* Actor = Cast<APlayerCharacter>(Target);
		if (!Actor) return false;
		
		const float Speed = Actor->UpdatedBaseAttributesComponent->GetVelocitySize();
		if (Speed > MinSpeedThreshold && Speed < MaxSpeedThreshold) return true;
		
		return false;
	}
	
	virtual FString GetRuleName() const override
	{
		return FString::Printf(TEXT("FActorRunPivotsRule"));
	}
};
