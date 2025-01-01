// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Commons/Rules/FRuleManager.h"
#include "NewProject/Commons/Rules/SelectorPoseSearchDatabaseRules/FActorIdleRule.h"

/**
 * 
 */
class NEWPROJECT_API FPSD_DenseStandIdlesEntity : public FRuleManager
{
public:
	FPSD_DenseStandIdlesEntity()
	{
		UE_LOG(LogTemp, Warning, TEXT("Object of FPSD_DenseStandIdlesEntity created at %p"), this);
	}
	
	virtual ~FPSD_DenseStandIdlesEntity() override
	{
		UE_LOG(LogTemp, Warning, TEXT("Object of FPSD_DenseStandIdlesEntity deleted at %p"), this);
	}

	FString NameAsset = "PSD_Dense_Stand_Idles";
	FString PathAsset = "/Game/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Databases/Dense/PSD_Dense_Stand_Idles.PSD_Dense_Stand_Idles";

	// Inicializa as Rules para valicao
	virtual void Initialize() override
	{
		TSharedPtr<IRuleBase> Rule;
		if (Rule)
		{
			Rule = MakeShared<FActorIdleRule>();
			AddRule(Rule);
		}
	}

	virtual void PrintInformation() override
	{
		UE_LOG(LogTemp, Warning, TEXT("FPSD_DenseStandIdlesEntity exc method PrintInformation"));
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
