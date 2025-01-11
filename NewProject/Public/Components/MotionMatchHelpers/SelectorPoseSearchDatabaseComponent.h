// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NewProject/Enums/CharacterStates/PlayerCharacterStateEnum.h"
#include "NewProject/Interfaces/Helpers/EntityAsset.h"
#include "PoseSearch/PoseSearchDatabase.h"
#include "NewProject/Interfaces/MotionMatchHelpersComponents/SelectorPoseSearchDatabaseInterface.h"
#include "SelectorPoseSearchDatabaseComponent.generated.h"

UCLASS()
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

	virtual void BeginPlay() override;

	virtual UPoseSearchDatabase* GetDatabase() override;
	virtual void SetDatabaseCurrent(const uint32 Index) override;
	
	virtual void LoadDatabaseAsset(const FString& DirectoryEntity) override;
	virtual void DefaultDatabaseAsset(const FString& DirectoryEntityAsset) override;
	
	virtual void SetInterruptMode(EPoseSearchInterruptMode Mode) override;
	virtual EPoseSearchInterruptMode GetInterruptMode() override;

	virtual TArray<IEntityAsset*> GetEntitiesAsset() override;

	UFUNCTION()
	void OnState(EPlayerCharacterStateEnum CurrentState, EPlayerCharacterStateEnum PreviousState);

	UFUNCTION()
	void OnDeceleration(float PrevVelocity, float CurrentVelocity);

	UFUNCTION()
	void OnAcceleration(float PrevVelocity, float CurrentVelocity);

	UFUNCTION()
	virtual AActor* GetActor() override;

	bool bIsBlockingDeceleration;
	bool bIsBlockingAcceleration;

	TArray<IEntityAsset*> FoundHeaderFiles;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pose Search Database")
	TArray<UPoseSearchDatabase*> Databases;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pose Search Database")
	UPoseSearchDatabase* DatabaseCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pose Search Database")
	EPoseSearchInterruptMode InterruptModeCurrent = EPoseSearchInterruptMode::DoNotInterrupt;
};
