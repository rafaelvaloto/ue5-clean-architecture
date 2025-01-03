// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NewProject/Commons/Rules/FRuleManager.h"
#include "NewProject/Commons/Rules/SelectorPoseSearchDatabaseRules/FActorWalkStartRule.h"
#include "NewProject/Enums/PoseSearchDatabaseModeStates/SelectorDatabaseValidateRuleModeEnum.h"

class NEWPROJECT_API FPSD_SparseStandWalkStartsEntity : public FRuleManager
{
public:
	FPSD_SparseStandWalkStartsEntity()
	{
		NameAsset = "PSD_Walk_Starts";
		PathAsset = "/Game/Blueprints/MotionMatch/PSD_Walk_Starts.PSD_Walk_Starts";

		Callback = [](const std::vector<std::any>& Params) -> bool {
			if (Params.empty())
			{
				return true;
			}

			try
			{
				const ESelectorDatabaseValidateRuleModeEnum ModeValidate = std::any_cast<ESelectorDatabaseValidateRuleModeEnum>(Params[0]);

				if (ModeValidate == ESelectorDatabaseValidateRuleModeEnum::Velocity)
				{
					const float PreviousVelocity = std::any_cast<float>(Params[1]);
					const float CurrentVelocity = std::any_cast<float>(Params[2]);
				
					return CurrentVelocity > 0.01 && PreviousVelocity <= CurrentVelocity;
				}
				
				if (ModeValidate == ESelectorDatabaseValidateRuleModeEnum::StateCharacter)
				{
					const EPlayerCharacterStateEnum CurrentState = std::any_cast<EPlayerCharacterStateEnum>(Params[1]);
					const EPlayerCharacterStateEnum PreviousState = std::any_cast<EPlayerCharacterStateEnum>(Params[2]);
					
					return (CurrentState == EPlayerCharacterStateEnum::Walking && PreviousState == EPlayerCharacterStateEnum::Idle);
				}
				
			}
			catch (const std::bad_any_cast&)
			{
				UE_LOG(LogTemp, Error, TEXT("Nao foi possivel converter os parametros, os tipos estavam errados!"));
				return false;
			}
			
			return false;
		};
	}

	virtual ~FPSD_SparseStandWalkStartsEntity() override
	{
		UE_LOG(LogTemp, Warning, TEXT("Object of FPSD_SparseStandWalkStartsEntity deleted at %p"), this);
	}

	virtual ESelectorDatabaseValidateRuleModeEnum GetTypeValidateRule() override
	{
		return ESelectorDatabaseValidateRuleModeEnum::VelocityAndState;
	}

	// Inicializa as Rules para valicao
	virtual void Initialize() override
	{
		const TSharedPtr<IRuleBase> Rule = MakeShared<FActorWalkStartRule>();
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
		UE_LOG(LogTemp, Warning, TEXT("PSD_SparseStandWalkStartsEntity exc method PrintInformation"));
	}
};
