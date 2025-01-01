// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/SelectorPoseSearchDatabaseComponent/UpdateNodePoseSearchDatabaseUseCase.h"
#include "Components/MotionMatchHelpers/SelectorPoseSearchDatabaseComponent.h"

void UUpdateNodePoseSearchDatabaseUseCase::Handle
(
	const TScriptInterface<ISelectorPoseSearchDatabaseInterface>& Component,
	EPlayerCharacterStateEnum CurrentState,
	EPlayerCharacterStateEnum PreviousState
)
{
	TArray<TSharedPtr<IEntityAsset>> EntitiesAssets = Component->GetEntitiesAsset();

	int32 Index = 0;
	for (TSharedPtr<IEntityAsset> Entity : EntitiesAssets)
	{
		UE_LOG(LogTemp, Warning, TEXT("Entity: %s"), *Entity->GetNameAsset())

		if (
			Entity->GetNameAsset() == TEXT("PSD_Sparse_Stand_Walk_Starts") &&
			Entity->ValidWhen(ValidWhenTransitionIdleToWalk, { CurrentState, PreviousState })
		)
		{
			UE_LOG(LogTemp, Warning, TEXT("ValidWhen: ValidWhenTransitionIdleToWalk"))

			Entity->Initialize();
			UE_LOG(LogTemp, Warning, TEXT("ValidWhen: ValidWhenTransitionIdleToWalk Initialize()"))

			if (Entity->ValidateAll(Component->GetActor()))
			{
				UE_LOG(LogTemp, Warning, TEXT("ValidWhen: ValidWhenTransitionIdleToWalk ValidateAll"))
				Component->SetDatabaseCurrent(Index);
			}
		}
		
		if (
			Entity->GetNameAsset() == TEXT("PSD_Dense_Stand_Idles") &&
			CurrentState == EPlayerCharacterStateEnum::Idle
		)
		{
			UE_LOG(LogTemp, Warning, TEXT("ValidWhen: CurrentState == EPlayerCharacterStateEnum::Idle"))

			Entity->Initialize();
			UE_LOG(LogTemp, Warning, TEXT("ValidWhen: CurrentState == EPlayerCharacterStateEnum::Idle"))

			if (Entity->ValidateAll(Component->GetActor()))
			{
				UE_LOG(LogTemp, Warning, TEXT("ValidWhen: CurrentState == EPlayerCharacterStateEnum::Idle"))
				Component->SetDatabaseCurrent(Index);
			}
		}
		
		Index++; // Incrementa o índice
	}
}
