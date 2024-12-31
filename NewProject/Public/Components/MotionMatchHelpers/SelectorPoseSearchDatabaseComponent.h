// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NewProject/Interfaces/Helpers/EntityAsset.h"
#include "PoseSearch/PoseSearchDatabase.h"
#include "NewProject/Interfaces/MotionMatchHelpersComponents/SelectorPoseSearchDatabaseInterface.h"
#include "SelectorPoseSearchDatabaseComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEWPROJECT_API USelectorPoseSearchDatabaseComponent : public UActorComponent, public ISelectorPoseSearchDatabaseInterface
{
	GENERATED_BODY()
	// 'PSD_Sparse_Stand_Walk_Starts.PSD_Sparse_Stand_Walk_Starts'
	// 'PSD_Sparse_Stand_Walk_Loops.PSD_Sparse_Stand_Walk_Loops'
	// 'PSD_Sparse_Stand_Run_Starts.PSD_Sparse_Stand_Run_Starts'
	// 'PSD_Sparse_Stand_Run_Loops.PSD_Sparse_Stand_Run_Loops'

public:
	USelectorPoseSearchDatabaseComponent();
	virtual ~USelectorPoseSearchDatabaseComponent() override;

	virtual UPoseSearchDatabase* GetDatabase(uint32 Index) override;
	virtual void LoadDatabaseAsset(const FString& DirectoryEntity) override;

	TArray<TSharedPtr<IEntityAsset>> FoundHeaderFiles;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pose Search Database")
	TArray<UPoseSearchDatabase*> Databases;
};
