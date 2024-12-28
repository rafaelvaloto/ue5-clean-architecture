// Fill out your copyright notice in the Description page of Project Settings.


#include "NewProject/Public/UseCases/SplineDrawComponent/TrajectoryRuntimeDrawUseCase.h"
#include "Components/StaticMeshActor/SplineDrawComponent.h"

UTrajectoryRuntimeDrawUseCase::UTrajectoryRuntimeDrawUseCase()
{
	//
}

void UTrajectoryRuntimeDrawUseCase::Handle
(
	const TScriptInterface<ISplineDrawComponentInterface>& SplineBallComponentInterface,
	const FVector& Input,
	const float DeltaTime
)
{
	if (
		const float Distance = SplineBallComponentInterface->GetDistance();
		Distance > 0.0f
	)
	{
		const float DistanceAt = SplineBallComponentInterface->GetCurrentDistance();
		const float VelocityAt = SplineBallComponentInterface->GetCurrentVelocity();
		const float CurrentDistance = DistanceAt + (VelocityAt * DeltaTime);

		SplineBallComponentInterface->SetCurrentDistance(CurrentDistance);
		if (CurrentDistance > Distance)
		{
			SplineBallComponentInterface->SetCurrentDistance(Distance);
			SplineBallComponentInterface->SetComponentVelocity(FVector::ZeroVector);
			return;
		}

		return;
	}

	const float Average = SplineBallComponentInterface->CalculateSplineLength(Input);
	SplineBallComponentInterface->SetDistance(Average * 1.4f);
	SplineBallComponentInterface->AddSplinePointFunction();

	// Input * Force 
	const FVector LinearVelocity = Input.GetSafeNormal() * 200.0f;
	SplineBallComponentInterface->SetComponentVelocity(LinearVelocity);
}
