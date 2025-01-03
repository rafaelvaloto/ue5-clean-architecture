// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/SelectorPoseSearchDatabaseComponent/UpdateNodePoseSearchDatabaseUseCase.h"
#include "Components/MotionMatchHelpers/SelectorPoseSearchDatabaseComponent.h"
#include "NewProject/Enums/PoseSearchDatabaseModeStates/SelectorDatabaseValidateRuleModeEnum.h"

void UUpdateNodePoseSearchDatabaseUseCase::Handle
(
	const TScriptInterface<ISelectorPoseSearchDatabaseInterface>& Component,
	EPlayerCharacterStateEnum CurrentState,
	EPlayerCharacterStateEnum PreviousState
)
{
	TArray<TSharedPtr<IEntityAsset>> EntitiesAssets = Component->GetEntitiesAsset();

	int32 Index = 0;
	for (const TSharedPtr<IEntityAsset>& Entity : EntitiesAssets)
	{
		Entity->ListRules();

		UE_LOG(LogTemp, Error, TEXT("Entity %s"), *Entity->GetNameAsset());
		UE_LOG(LogTemp, Error, TEXT("GetTypeValidateRule %d"), Entity->GetTypeValidateRule());
		UE_LOG(LogTemp, Error, TEXT("ESelectorDatabaseValidateRuleModeEnum %d"), ESelectorDatabaseValidateRuleModeEnum::StateCharacter);

		// Filtrar apenas entidades de um tipo específico
		if (
			Entity->GetTypeValidateRule() == ESelectorDatabaseValidateRuleModeEnum::All ||
			Entity->GetTypeValidateRule() == ESelectorDatabaseValidateRuleModeEnum::Velocity
		)
		{
			UE_LOG(LogTemp, Warning, TEXT("Continue %d"), Entity->GetTypeValidateRule());
			Index++;
			continue;
		}

		if (
			CurrentState == EPlayerCharacterStateEnum::Idle
		)
		{
			UE_LOG(LogTemp, Error, TEXT("Idle"));
			Component->SetInterruptMode(EPoseSearchInterruptMode::DoNotInterrupt);
			Component
				->DefaultDatabaseAsset(
					"/Game/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Databases/Dense/PSD_Dense_Stand_Idles.PSD_Dense_Stand_Idles"
				);
			Component->SetDatabaseCurrent(Index);
			break;
		}

		if (
			Entity->ValidateAll(
				Component->GetActor(),
				{
					ESelectorDatabaseValidateRuleModeEnum::StateCharacter, CurrentState, PreviousState
				}
			)
		)
		{
			Component->SetInterruptMode(EPoseSearchInterruptMode::InterruptOnDatabaseChange);
			Component->SetDatabaseCurrent(Index);

			Component->SetInterruptMode(EPoseSearchInterruptMode::DoNotInterrupt);
			break;
		}

		Index++;
	}

	UE_LOG(LogTemp, Error, TEXT("Selected Database %s"), *Component->GetDatabase()->GetName());
}
