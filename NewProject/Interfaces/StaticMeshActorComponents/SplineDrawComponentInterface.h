// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SplineDrawComponentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class USplineDrawComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NEWPROJECT_API ISplineDrawComponentInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetComponentVelocity(FVector Velocity) = 0;
	virtual void AddSplinePointFunction() = 0;
	
	virtual void SetDistance(float Value) = 0;
	virtual void SetCurrentDistance(float CurrentDistance) = 0;
	
	virtual float GetDistance() = 0;
	virtual float GetCurrentDistance() = 0;
	virtual float GetCurrentVelocity() = 0;
	virtual float CalculateSplineLength(FVector TrajectoryEnd) = 0;
};
