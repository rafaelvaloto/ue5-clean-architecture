// Fill out your copyright notice in the Description page of Project Settings.


#include "NewProject/Public/UseCases/SplineDrawComponent/TrajectoryRuntimeDrawUseCase.h"
#include "Components/StaticMeshActor/SplineDrawComponent.h"

UTrajectoryRuntimeDrawUseCase::UTrajectoryRuntimeDrawUseCase()
{
	//
}

void UTrajectoryRuntimeDrawUseCase::Handle
(
	TScriptInterface<ISplineDrawComponentInterface> SplineBallComponentInterface,
	const FVector& Input,
	float DeltaTime
)
{
	float Distance = SplineBallComponentInterface->GetDistance();
	if (Distance > 0.0f)
	{
		float DistanceAt = SplineBallComponentInterface->GetCurrentDistance();
		float VelocityAt = SplineBallComponentInterface->GetCuurentVelocity();
		float CurrentDistance = DistanceAt + (VelocityAt * DeltaTime);

		SplineBallComponentInterface->SetCurrentDistance(CurrentDistance);
		if (CurrentDistance > Distance)
		{
			SplineBallComponentInterface->SetCurrentDistance(Distance);
			SplineBallComponentInterface->SetComponentVelocity(FVector::ZeroVector);
			return;
		}

		return;
	}

	float Average = SplineBallComponentInterface->CalculateSplineLength(Input);
	SplineBallComponentInterface->SetDistance(Average * 1.4f);
	SplineBallComponentInterface->AddSplinePointFunction();

	// Input * Force 
	FVector LinearVelocity = Input.GetSafeNormal() * 200.0f;
	SplineBallComponentInterface->SetComponentVelocity(LinearVelocity);
}
