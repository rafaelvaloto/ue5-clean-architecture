// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "StartInpulseTacklerNotify.generated.h"

/**
 * 
 */
UCLASS()
class NEWPROJECT_API UStartInpulseTacklerNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	// Lógica do Notify
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
