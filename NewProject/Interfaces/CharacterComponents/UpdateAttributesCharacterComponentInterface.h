// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UpdateAttributesCharacterComponentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UUpdateAttributesCharacterComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NEWPROJECT_API IUpdateAttributesCharacterComponentInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetLocationCurrent(FVector VelocityAt) = 0;
	virtual void SetVelocityCurrent(FVector VelocityAt) = 0;

	
	virtual FVector GetVelocityCurrent() = 0;
	virtual FVector GetPreviousVelocity() = 0;
	virtual FVector GetLocationCurrent() = 0;
	virtual FVector GetPreviousLocation() = 0;
	virtual float GetMagnitudeAcceleration() = 0;

	virtual void DetectDirectionChange(float DeltaTime) = 0;
	virtual bool IsDetectedDirectionChange() = 0;
	
	virtual float GetVelocitySize() = 0;
	virtual float GetVelocitySize2D() = 0;
	virtual float GetPreviousVelocitySize() = 0;
};
