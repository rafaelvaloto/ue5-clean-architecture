// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RuleBase.h"
#include "NewProject/Enums/PoseSearchDatabaseModeStates/SelectorDatabaseValidateRuleModeEnum.h"

#include <any>
#include <vector>

/**
 * 
 */
class NEWPROJECT_API IEntityAsset
{
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual ~IEntityAsset() = default;

	virtual FString GetNameAsset() = 0;
	virtual FString GetPathAsset() = 0;
	virtual TArray<ESelectorDatabaseValidateRuleModeEnum> GetTypesValidateRule() = 0;

	virtual void ListRules() = 0;
	virtual void AddRule(IRuleBase* Rule) = 0;
	virtual bool ValidWhen(const std::vector<std::any>& Params) = 0;
	virtual bool ValidateAll(const UObject* Target, const std::vector<std::any>& Params) = 0;
	
	virtual void Initialize() = 0;
	virtual void PrintInformation() = 0;
};
