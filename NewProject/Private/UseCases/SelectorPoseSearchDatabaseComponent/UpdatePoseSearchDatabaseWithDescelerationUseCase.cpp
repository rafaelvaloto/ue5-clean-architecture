// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/SelectorPoseSearchDatabaseComponent/UpdatePoseSearchDatabaseWithDescelerationUseCase.h"

#include "PoseSearch/PoseSearchDatabase.h"

void UUpdatePoseSearchDatabaseWithDescelerationUseCase::Handle
(
	const TScriptInterface<ISelectorPoseSearchDatabaseInterface>& Component,
	float PreviousVelocity,
	float CurrentVelocity
)
{
	TArray<TSharedPtr<IEntityAsset>> EntitiesAssets = Component->GetEntitiesAsset();

	int32 Index = 0;
	for (const TSharedPtr<IEntityAsset> Entity : EntitiesAssets)
	{
		UE_LOG(LogTemp, Warning, TEXT("Entity %s"), *Entity->GetNameAsset());
		UE_LOG(LogTemp, Warning, TEXT("GetTypeValidateRule %d"), Entity->GetTypeValidateRule());
		UE_LOG(LogTemp, Warning, TEXT("ESelectorDatabaseValidateRuleModeEnum %d"), ESelectorDatabaseValidateRuleModeEnum::StateCharacter);
		
		// Filtrar apenas entidades de um tipo específico
		if (
			Entity->GetTypeValidateRule() == ESelectorDatabaseValidateRuleModeEnum::All ||
			Entity->GetTypeValidateRule() == ESelectorDatabaseValidateRuleModeEnum::StateCharacter
		)
		{
			UE_LOG(LogTemp, Warning, TEXT("Continue %d"), Entity->GetTypeValidateRule());
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
			Component->SetInterruptMode(EPoseSearchInterruptMode::InterruptOnDatabaseChange);
			Component->SetDatabaseCurrent(Index);

			Component->SetInterruptMode(EPoseSearchInterruptMode::DoNotInterrupt);
			break;
		}
		
		Index++;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Selected Database %s"), *Component->GetDatabase()->GetName());
}
