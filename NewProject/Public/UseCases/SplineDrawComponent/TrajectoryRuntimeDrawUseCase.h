// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Interfaces/StaticMeshActorComponents/SplineDrawComponentInterface.h"
#include "UObject/Object.h"
#include "TrajectoryRuntimeDrawUseCase.generated.h"

/**
 * 
 */
UCLASS()
class NEWPROJECT_API UTrajectoryRuntimeDrawUseCase : public UObject
{
	GENERATED_BODY()

public:
	UTrajectoryRuntimeDrawUseCase();

	static void Handle
	(
		TScriptInterface<ISplineDrawComponentInterface> SplineBallComponentInterface,
		const FVector& Input,
		float DeltaTime
	);
};
