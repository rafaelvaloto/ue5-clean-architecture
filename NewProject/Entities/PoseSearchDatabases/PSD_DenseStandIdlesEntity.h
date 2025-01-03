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
	}

	virtual ~FPSD_DenseStandIdlesEntity() override
	{
		UE_LOG(LogTemp, Warning, TEXT("Object of FPSD_DenseStandIdlesEntity deleted at %p"), this);
	}

	virtual ESelectorDatabaseValidateRuleModeEnum GetTypeValidateRule() override
	{
		return ESelectorDatabaseValidateRuleModeEnum::StateCharacter;
	}
	
	// Inicializa as Rules para valicao
	virtual void Initialize() override
	{
		const TSharedPtr<IRuleBase> Rule = MakeShared<FActorIdleRule>();
		AddRule(Rule);
	}

	virtual void ListRules() override
	{
		for (const TSharedPtr<IRuleBase> Rule : Rules)
		{
			UE_LOG(LogTemp, Log, TEXT("Listando regras: %s"), *Rule->GetRuleName());
		}
	}

	virtual void PrintInformation() override
	{
		UE_LOG(LogTemp, Warning, TEXT("FPSD_DenseStandIdlesEntity exc method PrintInformation"));
	}
};
