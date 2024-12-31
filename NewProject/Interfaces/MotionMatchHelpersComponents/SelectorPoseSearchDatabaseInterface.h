// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PoseSearch/PoseSearchDatabase.h"
#include "SelectorPoseSearchDatabaseInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class USelectorPoseSearchDatabaseInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NEWPROJECT_API ISelectorPoseSearchDatabaseInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void LoadDatabaseAsset(const FString& DirectoryEntity) = 0;
	virtual UPoseSearchDatabase* GetDatabase(uint32 Index) = 0;
};
