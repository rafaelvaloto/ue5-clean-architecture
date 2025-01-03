// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Commons/Rules/FRuleManager.h"
#include "NewProject/Commons/Rules/SelectorPoseSearchDatabaseRules/FActorWalkStopRule.h"
#include "NewProject/Interfaces/Helpers/RuleBase.h"

/**
 * 
 */
class NEWPROJECT_API FPSD_SparseStandWalkStopsEntity : public FRuleManager
{
public:
	FPSD_SparseStandWalkStopsEntity()
	{
		NameAsset = "PSD_Sparse_Stand_Walk_Stops";
		PathAsset =
			"/Game/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Databases/Sparse/PSD_Sparse_Stand_Walk_Stops.PSD_Sparse_Stand_Walk_Stops";

		Callback = [](const std::vector<std::any>& Params) -> bool
		{
			if (Params.empty())
			{
				return false;
			}

			try
			{
				const ESelectorDatabaseValidateRuleModeEnum ModeValidate = std::any_cast<
					ESelectorDatabaseValidateRuleModeEnum>(Params[0]);

				if (ModeValidate == ESelectorDatabaseValidateRuleModeEnum::Velocity)
				{
					const float CurrentVelocity = std::any_cast<float>(Params[1]);
					const float PreviousVelocity = std::any_cast<float>(Params[2]);

					if (const bool bIsValid = PreviousVelocity > CurrentVelocity; !bIsValid)
					{
						UE_LOG(LogTemp, Error, TEXT("PreviousVelocity: %f"), PreviousVelocity);
						UE_LOG(LogTemp, Error, TEXT("CurrentVelocity: %f"), CurrentVelocity);
						return false;
					}

					return true;
				}
			}
			catch (const std::bad_any_cast&)
			{
				UE_LOG(LogTemp, Warning, TEXT("Catch"));
				return false; // Os tipos estavam errados
			}

			return false;
		};
	}

	~FPSD_SparseStandWalkStopsEntity()
	{
		UE_LOG(LogTemp, Warning, TEXT("Object of FPSD_SparseStandWalkStopsEntity deleted at %p"), this);
	}

	virtual ESelectorDatabaseValidateRuleModeEnum GetTypeValidateRule() override
	{
		return ESelectorDatabaseValidateRuleModeEnum::Velocity;
	}

	// Inicializa as Rules para valicao
	virtual void Initialize() override
	{
		const TSharedPtr<IRuleBase> Rule = MakeShared<FActorWalkStopRule>();
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
		UE_LOG(LogTemp, Warning, TEXT("FPSD_SparseStandWalkStopsEntity exc method PrintInformation"));
	}
};
