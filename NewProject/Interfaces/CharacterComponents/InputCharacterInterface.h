// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InputCharacterInterface.generated.h"



// This class does not need to be modified.
UINTERFACE()
class UInputCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NEWPROJECT_API IInputCharacterInterface
{
	GENERATED_BODY()
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Move(FVector InputController) = 0;
	virtual void ControlYaw(const float InputValue) = 0;
	virtual void SetBlockMove(const bool bIsBlocked) = 0;
	virtual bool GetBlockMove() = 0;
};
