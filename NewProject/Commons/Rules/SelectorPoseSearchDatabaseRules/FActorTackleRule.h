// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Interfaces/Helpers/RuleBase.h"

/**
 * 
 */
class NEWPROJECT_API FActorTackleRule final : public IRuleBase
{
public:
	explicit FActorTackleRule()
	{
	}

	virtual ~FActorTackleRule() override
	{
	}

	virtual bool Validate(const UObject* Target) const override
	{
		return true;
	}
	
	virtual FString GetRuleName() const override
	{
		return FString::Printf(TEXT("FActorTackleRule"));
	}
};
