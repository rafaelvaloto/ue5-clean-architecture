// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Interfaces/Helpers/RuleBase.h"

/**
 * 
 */
class NEWPROJECT_API FActorWalkStartRule final : public IRuleBase
{
	FVector DesiredLocation;
	float Radius;

public:
	FActorWalkStartRule(const FVector& InDesiredLocation, float InRadius)
		: DesiredLocation(InDesiredLocation), Radius(InRadius) {}

	virtual bool Validate(const UObject* Target) const override
	{
		const AActor* Actor = Cast<AActor>(Target);
		if (!Actor) return false;

		// Calcula a distância e avalia a regra
		return FVector::Dist(Actor->GetActorLocation(), DesiredLocation) <= Radius;
	}

	virtual FString GetRuleName() const override
	{
		return FString::Printf(TEXT("Actor Walk Start Rule: Dentro de %.2f unidades de %s"), 
							   Radius, *DesiredLocation.ToString());
	}
};
