// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class NEWPROJECT_API IRuleBase
{
	
public:
	virtual ~IRuleBase() = default;
	virtual bool Validate(const UObject* Target) const = 0;
	virtual FString GetRuleName() const = 0;
};
