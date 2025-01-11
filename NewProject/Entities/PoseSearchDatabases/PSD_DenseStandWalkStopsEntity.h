// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Commons/Rules/FRuleManager.h"
#include "NewProject/Commons/Rules/SelectorPoseSearchDatabaseRules/FActorWalkStopRule.h"

class NEWPROJECT_API FPSD_DenseStandWalkStopsEntity : public FRuleManager
{
	
public:
	FPSD_DenseStandWalkStopsEntity()
	{
		NameAsset = "PSD_Dense_Stand_Walk_Stops";
		PathAsset = "/Game/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Databases/Dense/PSD_Dense_Stand_Walk_Stops.PSD_Dense_Stand_Walk_Stops";
		
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

					if (const bool bIsValid = PreviousVelocity < CurrentVelocity; bIsValid)
					{
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

	virtual ~FPSD_DenseStandWalkStopsEntity() override
	{
		UE_LOG(LogTemp, Warning, TEXT("Object of PSD_DenseStandWalkStopsEntity deleted at %p"), this);
	}

	virtual TArray<ESelectorDatabaseValidateRuleModeEnum> GetTypesValidateRule() override
	{
		return {
			ESelectorDatabaseValidateRuleModeEnum::Deceleration
		};
	}

	// Inicializa as Rules para valicao
	virtual void Initialize() override
	{
		IRuleBase* Rule = new FActorWalkStopRule();
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
		UE_LOG(LogTemp, Warning, TEXT("PSD_DenseStandWalkStopsEntity exc method PrintInformation"));
	}
};
