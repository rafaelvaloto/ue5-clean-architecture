// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NewProject/Interfaces/StaticMeshActorComponents/CurrentBallComponentInterface.h"
#include "BallControllUseCase.generated.h"

/**
 * 
 */
UCLASS()
class NEWPROJECT_API UBallControllUseCase : public UObject
{
	GENERATED_BODY()

public:
	static void Handle(
		const TScriptInterface<ICurrentBallComponentInterface>& CurrentBallComponentRef,
		const FVector& ForwardVector,
		const FVector& FootLocation
	);
};
