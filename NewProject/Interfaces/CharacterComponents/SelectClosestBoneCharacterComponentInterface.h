// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NewProject/Enums/CharacterStates/SelectClosestBoneCharacterEnum.h"
#include "SelectClosestBoneCharacterComponentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class USelectClosestBoneCharacterComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NEWPROJECT_API ISelectClosestBoneCharacterComponentInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual ESelectClosestBoneCharacterEnum SelectClosestFootBoneToBall(AActor* BallActor) = 0;
	virtual void SetFoot(ESelectClosestBoneCharacterEnum FootAt) = 0;
	virtual ESelectClosestBoneCharacterEnum GetFoot() = 0;
};
