// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RuleBase.h"

/**
 * 
 */
class NEWPROJECT_API IEntityAsset
{

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual ~IEntityAsset() = default;
	
	FString NameAsset = "";
	FString PathAsset = "";
	
	TArray<TSharedPtr<IRuleBase>> Rules;
	
	virtual FString GetNameAsset() = 0;
	virtual FString GetPathAsset() = 0;
	
	virtual void AddRule(const TSharedPtr<IRuleBase> Rule) = 0;
	virtual bool ValidateAll(const UObject* Target) = 0;
	virtual void ListRules() = 0;
	virtual void PrintInformation() = 0;
	virtual void Initialize() = 0;
};
