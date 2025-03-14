﻿// Fill out your copyright notice in the Description page of Project Settings.

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
			try
			{
				if (Params.empty())
				{
					return false;
				}

				const ESelectorDatabaseValidateRuleModeEnum ModeValidate = std::any_cast<
					ESelectorDatabaseValidateRuleModeEnum>(Params[0]);

				if (
					ModeValidate == ESelectorDatabaseValidateRuleModeEnum::StateCharacter
					)
				{
					const EPlayerCharacterStateEnum CurrentState = std::any_cast<EPlayerCharacterStateEnum>(Params[1]);
					return CurrentState == EPlayerCharacterStateEnum::RunningPivot;
				}

				if (
					ModeValidate == ESelectorDatabaseValidateRuleModeEnum::Acceleration ||
					ModeValidate == ESelectorDatabaseValidateRuleModeEnum::Velocity
				)
				{
					return true;
				}
				
				return false;
			}
			catch (const std::bad_any_cast&)
			{
				return false;
			}
		};
	}

	virtual ~FPSD_DenseStandRunPivotsAllEntity() override
	{
		UE_LOG(LogTemp, Warning, TEXT("Object of PSD_DenseStandRunPivotsAllEntity deleted at %p"), this);
	}

	virtual TArray<ESelectorDatabaseValidateRuleModeEnum> GetTypesValidateRule() override
	{
		return {
			ESelectorDatabaseValidateRuleModeEnum::StateCharacter,
			ESelectorDatabaseValidateRuleModeEnum::Acceleration,
			ESelectorDatabaseValidateRuleModeEnum::Velocity,
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
