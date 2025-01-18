// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Commons/Rules/FRuleManager.h"
#include "NewProject/Commons/Rules/SelectorPoseSearchDatabaseRules/FActorIdleRule.h"
#include "NewProject/Commons/Rules/SelectorPoseSearchDatabaseRules/FActorTackleRule.h"

/**
 * 
 */
class NEWPROJECT_API FPSD_RobootA1TackleEntity : public FRuleManager
{
public:
	FPSD_RobootA1TackleEntity()
	{
		NameAsset = "PSD_Roboot_A1_Tackle";
		PathAsset = "/Game/Blueprints/MotionMatch/PSD_Roboot_A1_Tackle.PSD_Roboot_A1_Tackle";

		Callback = [](const std::vector<std::any>& Params) -> bool
		{
			return false;
		};
	}

	virtual ~FPSD_RobootA1TackleEntity() override
	{
		UE_LOG(LogTemp, Warning, TEXT("Object of PSD_RobootA1TackleEntity deleted at %p"), this);
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
		IRuleBase* Rule = new FActorTackleRule();
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
		UE_LOG(LogTemp, Warning, TEXT("PSD_RobootA1TackleEntity exc method PrintInformation"));
	}
};
