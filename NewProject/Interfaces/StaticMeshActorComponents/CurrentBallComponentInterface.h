// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CurrentBallComponentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UCurrentBallComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NEWPROJECT_API ICurrentBallComponentInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual AActor* CurrentBall() = 0;
	virtual bool IsContact() = 0;
};
