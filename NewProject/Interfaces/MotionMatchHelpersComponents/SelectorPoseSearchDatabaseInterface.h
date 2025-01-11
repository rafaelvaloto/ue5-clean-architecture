// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Interfaces/Helpers/EntityAsset.h"
#include "UObject/Interface.h"
#include "PoseSearch/PoseSearchLibrary.h"
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
	virtual void DefaultDatabaseAsset(const FString& DirectoryEntityAsset) = 0;
	virtual UPoseSearchDatabase* GetDatabase() = 0;
	virtual void SetDatabaseCurrent(const uint32 Index) = 0;
	virtual TArray<IEntityAsset*> GetEntitiesAsset() = 0;
	virtual void SetInterruptMode(EPoseSearchInterruptMode Mode) = 0;
	virtual EPoseSearchInterruptMode GetInterruptMode() = 0;

	virtual AActor* GetActor() = 0;
};
