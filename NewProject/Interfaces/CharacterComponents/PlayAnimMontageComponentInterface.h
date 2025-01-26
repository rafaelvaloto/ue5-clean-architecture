// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayAnimMontageComponentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPlayAnimMontageComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NEWPROJECT_API IPlayAnimMontageComponentInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void PlayDynamicMontage(UAnimSequence* AnimationSequence, FName SlotName, float PlayRate, float NewPlayRate = 0.0f, float TimeToChangePlayRate = 0.0, bool Loop = false) = 0;
	virtual void SetDynamicMontages(TArray<UAnimSequence*> AnimationSequences, FName SlotName, float PlayRate, float NewPlayRate = 0.0f, float TimeToChangePlayRate = 0.0, bool Loop = false) = 0;
	virtual void DefineIndexPlayDynamicMontage(int32 Index, FName SlotName, float PlayRate, bool Loop = false) = 0;
};
