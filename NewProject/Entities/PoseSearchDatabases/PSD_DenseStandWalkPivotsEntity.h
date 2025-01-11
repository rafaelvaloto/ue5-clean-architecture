// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Enums/CharacterStates/PlayerCharacterStateEnum.h"
#include "NewProject/Enums/PoseSearchDatabaseModeStates/SelectorDatabaseValidateRuleModeEnum.h"
#include "NewProject/Commons/Rules/SelectorPoseSearchDatabaseRules/FActorWalkPivotsRule.h"
#include "NewProject/Commons/Rules/FRuleManager.h"


/**
 * 
 */
class NEWPROJECT_API FPSD_DenseStandWalkPivotsEntity : public FRuleManager
{

public:
	FPSD_DenseStandWalkPivotsEntity()
	{
		NameAsset = "PSD_Dense_Stand_Walk_Pivots";
		PathAsset = "/Game/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Databases/Dense/PSD_Dense_Stand_Walk_Pivots.PSD_Dense_Stand_Walk_Pivots";

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
					return CurrentState == EPlayerCharacterStateEnum::WalkingPivot;
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

	virtual ~FPSD_DenseStandWalkPivotsEntity() override
	{
		UE_LOG(LogTemp, Warning, TEXT("Object of PSD_DenseStandWalkPivotsEntity deleted at %p"), this);
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
		IRuleBase* Rule = new FActorWalkPivotsRule();
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
		UE_LOG(LogTemp, Warning, TEXT("PSD_DenseStandWalkLoopsEntity exc method PrintInformation"));
	}
};
