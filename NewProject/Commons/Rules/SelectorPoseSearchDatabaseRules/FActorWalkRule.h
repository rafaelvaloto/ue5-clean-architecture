// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Application/PlayerCharacter/PlayerCharacter.h"
#include "NewProject/Interfaces/Helpers/RuleBase.h"

/**
 * 
 */
class NEWPROJECT_API FActorWalkRule : public IRuleBase
{
	
public:
	virtual ~FActorWalkRule() override
	{
		UE_LOG(LogTemp, Warning, TEXT("FActorWalkRule destrutor chamado - %p"), this);
	}

	virtual bool Validate(const UObject* Target) const override
	{
		const APlayerCharacter* Actor = Cast<APlayerCharacter>(Target);
		if (!Actor) return false;

		const float Speed = Actor->UpdatedBaseAttributesComponent->GetVelocitySize();
		const float AccelMagnitude = Actor->UpdatedBaseAttributesComponent->GetMagnitudeAcceleration();

		return Speed < 20.0f && AccelMagnitude < 50.f;
	}

	virtual FString GetRuleName() const override
	{
		return FString::Printf(TEXT("FActorWalkRule"));
	}
};
