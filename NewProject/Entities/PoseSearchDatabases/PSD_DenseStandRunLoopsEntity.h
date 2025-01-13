// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <any>
#include <vector>

#include "CoreMinimal.h"
#include "NewProject/Commons/Rules/FRuleManager.h"
#include "NewProject/Commons/Rules/SelectorPoseSearchDatabaseRules/FActorRunRule.h"
#include "NewProject/Enums/CharacterStates/PlayerCharacterStateEnum.h"
#include "NewProject/Enums/PoseSearchDatabaseModeStates/SelectorDatabaseValidateRuleModeEnum.h"

/**
 * 
 */
class NEWPROJECT_API FPSD_DenseStandRunLoopsEntity : public FRuleManager
{
public:
	FPSD_DenseStandRunLoopsEntity()
	{
		NameAsset = "PSD_Dense_Stand_Run_Loops";
		PathAsset = "/Game/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Databases/Dense/PSD_Dense_Stand_Run_Loops.PSD_Dense_Stand_Run_Loops";

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

				if (ModeValidate == ESelectorDatabaseValidateRuleModeEnum::StateCharacter)
				{
					const EPlayerCharacterStateEnum CurrentState = std::any_cast<EPlayerCharacterStateEnum>(Params[1]);
					return CurrentState == EPlayerCharacterStateEnum::Running;
				}

				if (ModeValidate == ESelectorDatabaseValidateRuleModeEnum::Velocity)
				{
					if (const float CurrentVelocity = std::any_cast<float>(Params[1]); CurrentVelocity > 20.f)
					{
						return true;
					}

					if (const float Acceleration = std::any_cast<float>(Params[3]); Acceleration > 50.f)
					{
						return true;
					}
				}

				return false;
			}
			catch (const std::bad_any_cast&)
			{
				UE_LOG(LogTemp, Error, TEXT("Nao foi possivel converter os parametros, os tipos estavam errados!"));
				return false;
			}
		};
	}

	virtual ~FPSD_DenseStandRunLoopsEntity() override
	{
		UE_LOG(LogTemp, Warning, TEXT("Object of FPSD_DenseStandRunLoopsEntity deleted at %p"), this);
	}

	virtual TArray<ESelectorDatabaseValidateRuleModeEnum> GetTypesValidateRule() override
	{
		return {
			ESelectorDatabaseValidateRuleModeEnum::Velocity,
			ESelectorDatabaseValidateRuleModeEnum::Acceleration
		};
	}

	// Inicializa as Rules para validacao
	virtual void Initialize() override
	{
		IRuleBase* Rule = new FActorRunRule();
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
		UE_LOG(LogTemp, Warning, TEXT("FPSD_DenseStandRunLoopsEntity exc method PrintInformation"));
	}
	
};
