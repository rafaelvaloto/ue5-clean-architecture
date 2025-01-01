// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Character/UpdateStateCharacterComponent.h"
#include "NewProject/Enums/CharacterStates/PlayerCharacterStateEnum.h"
#include "NewProject/Interfaces/MotionMatchHelpersComponents/SelectorPoseSearchDatabaseInterface.h"
#include "UObject/Object.h"
#include "UpdateNodePoseSearchDatabaseUseCase.generated.h"


/**
 * 
 */
UCLASS()
class NEWPROJECT_API UUpdateNodePoseSearchDatabaseUseCase : public UObject
{
	GENERATED_BODY()

public:
	static void Handle
	(
		const TScriptInterface<ISelectorPoseSearchDatabaseInterface>& Component,
		EPlayerCharacterStateEnum CurrentState,
		EPlayerCharacterStateEnum PreviousState
	);
};

inline std::function<bool(const std::vector<std::any>&)> ValidWhenTransitionIdleToWalk = [](const std::vector<std::any>& Params) -> bool {
	int32 Size  = Params.size();
	if (Size != 2)
	{
		
		UE_LOG(LogTemp, Warning, TEXT("Params.size() != 2 %d"), Size);
		return false; // Verifica o número esperado de parâmetros
	}

	try
	{
		EPlayerCharacterStateEnum CurrentState = std::any_cast<EPlayerCharacterStateEnum>(Params[0]);
		EPlayerCharacterStateEnum PreviousState = std::any_cast<EPlayerCharacterStateEnum>(Params[1]);

		UE_LOG(LogTemp, Warning, TEXT("CurrentState: %s"), *UUpdateStateCharacterComponent::GetStateDisplayName(CurrentState).ToString());
		UE_LOG(LogTemp, Warning, TEXT("PreviousState: %s"), *UUpdateStateCharacterComponent::GetStateDisplayName(PreviousState).ToString());
		
		return (CurrentState == EPlayerCharacterStateEnum::Walking && PreviousState == EPlayerCharacterStateEnum::Idle);
	}
	catch (const std::bad_any_cast&)
	{
		UE_LOG(LogTemp, Warning, TEXT("Catch"));
		return false; // Os tipos estavam errados
	}
};


