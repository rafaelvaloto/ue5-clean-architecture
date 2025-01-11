// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Commons/Rules/FRuleManager.h"
#include "NewProject/Commons/Rules/SelectorPoseSearchDatabaseRules/FActorRunPivotsRule.h"

/**
 * 
 */
class NEWPROJECT_API FPSD_DenseStandRunPivotsAllEntity : public FRuleManager
{
	
public:
	FPSD_DenseStandRunPivotsAllEntity()
	{
		NameAsset = "PSD_Dense_Stand_Run_Pivots";
		PathAsset = "/Game/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Databases/Dense/PSD_Dense_Stand_Run_Pivots.PSD_Dense_Stand_Run_Pivots";

		Callback = [](const std::vector<std::any>& Params) -> bool
		{
			return true;
		};
	}

	virtual ~FPSD_DenseStandRunPivotsAllEntity() override
	{
		UE_LOG(LogTemp, Warning, TEXT("Object of PSD_DenseStandRunPivotsAllEntity deleted at %p"), this);
	}

	virtual TArray<ESelectorDatabaseValidateRuleModeEnum> GetTypesValidateRule() override
	{
		return {
			ESelectorDatabaseValidateRuleModeEnum::StateCharacter
		};
	}

	// Inicializa as Rules para valicao
	virtual void Initialize() override
	{
		IRuleBase* Rule = new FActorRunPivotsRule();
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
		UE_LOG(LogTemp, Warning, TEXT("PSD_DenseStandRunPivotsAllEntity exc method PrintInformation"));
	}
};
