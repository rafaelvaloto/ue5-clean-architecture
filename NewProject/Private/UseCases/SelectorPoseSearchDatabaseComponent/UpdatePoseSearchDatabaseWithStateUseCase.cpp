// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/SelectorPoseSearchDatabaseComponent/UpdatePoseSearchDatabaseWithStateUseCase.h"
#include "Components/MotionMatchHelpers/SelectorPoseSearchDatabaseComponent.h"
#include "NewProject/Enums/PoseSearchDatabaseModeStates/SelectorDatabaseValidateRuleModeEnum.h"

bool UUpdatePoseSearchDatabaseWithStateUseCase::Handle
(
	const TScriptInterface<ISelectorPoseSearchDatabaseInterface>& Component,
	EPlayerCharacterStateEnum CurrentState,
	EPlayerCharacterStateEnum PreviousState
)
{
	TArray<IEntityAsset*> EntitiesAssets = Component->GetEntitiesAsset();

	int32 Index = 0;
	for (IEntityAsset* Entity : EntitiesAssets)
	{
		Entity->ListRules();
		
		UE_LOG(LogTemp, Error, TEXT("ESelectorDatabaseValidateRuleModeEnum %d"), ESelectorDatabaseValidateRuleModeEnum::StateCharacter);

		// Filtrar apenas entidades de um tipo específico
		if (
			!Entity->GetTypesValidateRule().Contains(ESelectorDatabaseValidateRuleModeEnum::StateCharacter)
		)
		{
			Index++;
			continue;
		}

		if (
			CurrentState == EPlayerCharacterStateEnum::Idle
		)
		{

			Component->SetInterruptMode(EPoseSearchInterruptMode::InterruptOnDatabaseChange);
			Component
				->DefaultDatabaseAsset(
					"/Game/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Databases/Dense/PSD_Dense_Stand_Idles.PSD_Dense_Stand_Idles"
				);
			Component->SetDatabaseCurrent(Index);

			Component->SetInterruptMode(EPoseSearchInterruptMode::DoNotInterrupt);
			break;
		}


		UE_LOG(LogTemp, Error, TEXT("Entity %s"), *Entity->GetNameAsset());
		
		if (
			Entity->ValidateAll(
				Component->GetActor(),
				{
					ESelectorDatabaseValidateRuleModeEnum::StateCharacter, CurrentState, PreviousState
				}
			)
		)
		{
			Component->SetDatabaseCurrent(Index);
		}
		Index++;
	}

	return true;
}
