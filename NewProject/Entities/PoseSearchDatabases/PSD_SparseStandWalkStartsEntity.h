// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NewProject/Commons/Rules/FRuleManager.h"
#include "NewProject/Commons/Rules/SelectorPoseSearchDatabaseRules/FActorWalkStartRule.h"

class NEWPROJECT_API FPSD_SparseStandWalkStartsEntity : public FRuleManager
{
public:
	FPSD_SparseStandWalkStartsEntity()
	{
		UE_LOG(LogTemp, Warning, TEXT("Object of FPSD_SparseStandWalkStartsEntity created at %p"), this);
	}

	virtual ~FPSD_SparseStandWalkStartsEntity() override
	{
		UE_LOG(LogTemp, Warning, TEXT("Object of FPSD_SparseStandWalkStartsEntity deleted at %p"), this);
	}

	FString NameAsset = "PSD_Sparse_Stand_Walk_Starts";
	FString PathAsset = "/Game/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Databases/Sparse/PSD_Sparse_Stand_Walk_Starts.PSD_Sparse_Stand_Walk_Starts";

	// Inicializa as Rules para valicao
	virtual void Initialize() override
	{
		TSharedPtr<IRuleBase> Rule;
		if (Rule)
		{
			Rule = MakeShared<FActorWalkStartRule>();
			AddRule(Rule);
		}
	}

	virtual void PrintInformation() override
	{
		UE_LOG(LogTemp, Warning, TEXT("PSD_SparseStandWalkStartsEntity exc method PrintInformation"));
	}

	virtual FString GetNameAsset() override
	{
		return NameAsset;
	}

	virtual FString GetPathAsset() override
	{
		return PathAsset;
	}
};
