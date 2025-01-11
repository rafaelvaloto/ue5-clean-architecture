// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Commons/Rules/FRuleManager.h"
#include "NewProject/Commons/Rules/SelectorPoseSearchDatabaseRules/FActorWalkStartRule.h"
#include "NewProject/Enums/PoseSearchDatabaseModeStates/SelectorDatabaseValidateRuleModeEnum.h"

class NEWPROJECT_API FPSD_DenseStandWalkStartsEntity : public FRuleManager
{

public:
	FPSD_DenseStandWalkStartsEntity()
	{
		NameAsset = "PSD_Dense_Stand_Walk_Starts";
		PathAsset = "/Game/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Databases/Dense/PSD_Dense_Stand_Walk_Starts.PSD_Dense_Stand_Walk_Starts";
		
		Callback = [](const std::vector<std::any>& Params) -> bool {

			try
			{
				if (Params.empty())
				{
					return false;
				}
				
				const ESelectorDatabaseValidateRuleModeEnum ModeValidate = std::any_cast<ESelectorDatabaseValidateRuleModeEnum>(Params[0]);

				if (ModeValidate == ESelectorDatabaseValidateRuleModeEnum::Velocity)
				{
					const float CurrentVelocity = std::any_cast<float>(Params[1]);
					const float PreviousVelocity = std::any_cast<float>(Params[2]);
				
					return CurrentVelocity > PreviousVelocity;
				}
				
				if (ModeValidate == ESelectorDatabaseValidateRuleModeEnum::StateCharacter)
				{
					const EPlayerCharacterStateEnum CurrentState = std::any_cast<EPlayerCharacterStateEnum>(Params[1]);
					const EPlayerCharacterStateEnum PreviousState = std::any_cast<EPlayerCharacterStateEnum>(Params[2]);
					
					return (CurrentState == EPlayerCharacterStateEnum::Walking && PreviousState == EPlayerCharacterStateEnum::Idle);
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

	virtual ~FPSD_DenseStandWalkStartsEntity() override
	{
		UE_LOG(LogTemp, Warning, TEXT("Object of PSD_DenseStandWalkStartsEntity deleted at %p"), this);
	}

	virtual TArray<ESelectorDatabaseValidateRuleModeEnum> GetTypesValidateRule() override
	{
		return {
			ESelectorDatabaseValidateRuleModeEnum::Velocity,
			ESelectorDatabaseValidateRuleModeEnum::Acceleration,
			ESelectorDatabaseValidateRuleModeEnum::StateCharacter
		};
	}

	// Inicializa as Rules para valicao
	virtual void Initialize() override
	{
		IRuleBase* Rule = new FActorWalkStartRule();
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
};
