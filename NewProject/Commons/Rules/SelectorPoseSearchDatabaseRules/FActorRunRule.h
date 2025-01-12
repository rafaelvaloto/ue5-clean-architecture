// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Application/PlayerCharacter/PlayerCharacter.h"

/**
 * 
 */
class NEWPROJECT_API FActorRunRule final : public IRuleBase
{
public:
	FActorRunRule()
	{
		UE_LOG(LogTemp, Warning, TEXT("FActorRunRule construtor chamado - %p"), this);
	}
	
	virtual ~FActorRunRule() override
	{
		UE_LOG(LogTemp, Warning, TEXT("FActorRunRule destrutor chamado - %p"), this);
	}

	virtual bool Validate(const UObject* Target) const override
	{
		const APlayerCharacter* Actor = Cast<APlayerCharacter>(Target);
		if (!Actor) return false;

		const float Speed = Actor->UpdatedBaseAttributesComponent->GetVelocitySize();
		const float AccelMagnitude = Actor->UpdatedBaseAttributesComponent->GetMagnitudeAcceleration();

		return Speed > 30.0f || AccelMagnitude > 100.f;
	}

	virtual FString GetRuleName() const override
	{
		return FString::Printf(TEXT("FActorWalkRule"));
	}
};
