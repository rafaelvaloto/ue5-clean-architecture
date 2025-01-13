// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Enums/CharacterStates/PlayerCharacterStateEnum.h"
#include "UObject/Interface.h"
#include "UpdateStateCharacterComponentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UUpdateStateCharacterComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NEWPROJECT_API IUpdateStateCharacterComponentInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetCurrentState(EPlayerCharacterStateEnum State) = 0;
	virtual EPlayerCharacterStateEnum GetState() = 0;
	virtual EPlayerCharacterStateEnum GetPeviousState() = 0;
};
