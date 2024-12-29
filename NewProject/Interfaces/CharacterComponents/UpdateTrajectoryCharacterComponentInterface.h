// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UpdateTrajectoryCharacterComponentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UUpdateTrajectoryCharacterComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NEWPROJECT_API IUpdateTrajectoryCharacterComponentInterface
{
	GENERATED_BODY()
public:
	virtual void OnMovementUpdated(float DeltaSeconds, FVector OldLocation, FVector OldVelocity) = 0;
};
