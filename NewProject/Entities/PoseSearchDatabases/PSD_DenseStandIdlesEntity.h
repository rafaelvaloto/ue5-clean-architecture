// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Commons/Rules/FRuleManager.h"
#include "NewProject/Commons/Rules/SelectorPoseSearchDatabaseRules/FActorIdleRule.h"

/**
 * 
 */
class NEWPROJECT_API FPSD_DenseStandIdlesEntity : public FRuleManager
{
	
public:
	FPSD_DenseStandIdlesEntity()
	{
		NameAsset = "PSD_Dense_Stand_Idles";
		PathAsset = "/Game/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Databases/Dense/PSD_Dense_Stand_Idles.PSD_Dense_Stand_Idles";

		Callback = [](const std::vector<std::any>& Params) -> bool
		{
			return true;
		};
	}

	virtual ~FPSD_DenseStandIdlesEntity() override
	{
		UE_LOG(LogTemp, Warning, TEXT("Object of PSD_DenseStandIdlesEntity deleted at %p"), this);
	}

	// Inicializa as Rules para valicao
	virtual void Initialize() override
	{
		IRuleBase* Rule = new FActorIdleRule();
		AddRule(Rule);
	}
	
	virtual void ListRules() override
	{
		for (IRuleBase* Rule : Rules)
		{
			UE_LOG(LogTemp, Log, TEXT("Listando regras: %s"), *Rule->GetRuleName());
		}
	}
	
	virtual void PrintInformation() override
	{
		UE_LOG(LogTemp, Warning, TEXT("PSD_SparseStandWalkStartsEntity exc method PrintInformation"));
	}

	virtual TArray<ESelectorDatabaseValidateRuleModeEnum> GetTypesValidateRule() override
	{
		return {
			ESelectorDatabaseValidateRuleModeEnum::StateCharacter
		};
	}
};
