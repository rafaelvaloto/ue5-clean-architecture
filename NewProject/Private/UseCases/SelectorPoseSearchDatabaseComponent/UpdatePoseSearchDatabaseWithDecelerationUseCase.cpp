// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/SelectorPoseSearchDatabaseComponent/UpdatePoseSearchDatabaseWithDecelerationUseCase.h"

#include "PoseSearch/PoseSearchDatabase.h"

void UUpdatePoseSearchDatabaseWithDecelerationUseCase::Handle
(
	const TScriptInterface<ISelectorPoseSearchDatabaseInterface>& Component,
	float PreviousVelocity,
	float CurrentVelocity
)
{
	TArray<IEntityAsset*> EntitiesAssets = Component->GetEntitiesAsset();

	int32 Index = 0;
	for (IEntityAsset* Entity : EntitiesAssets)
	{
		// Filtrar apenas entidades de um tipo específico
		if (
			!Entity->GetTypesValidateRule().Contains(ESelectorDatabaseValidateRuleModeEnum::Deceleration)
		)
		{
			Index++;
			continue;
		}

		if (
			Entity->ValidateAll(
				Component->GetActor(),
				{
					ESelectorDatabaseValidateRuleModeEnum::Velocity, CurrentVelocity, PreviousVelocity
				}
			)
		)
		{
			UE_LOG(LogTemp, Warning, TEXT("Mudou para Deleration"));
			Component->SetInterruptMode(EPoseSearchInterruptMode::InterruptOnDatabaseChange);
			Component->SetDatabaseCurrent(Index);
			Component->SetInterruptMode(EPoseSearchInterruptMode::DoNotInterrupt);
			break;
		}
		
		Index++;
	}
}
