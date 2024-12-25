// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Interfaces/StaticMeshActorComponents/SplineDrawComponentInterface.h"
#include "SplineDrawComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEWPROJECT_API USplineDrawComponent : public UActorComponent, public ISplineDrawComponentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USplineDrawComponent();

	virtual void SetDistance(float Value) override;
	virtual void SetCurrentDistance(float Value) override;
	virtual void SetComponentVelocity(FVector Velocity) override;
	virtual void AddSplinePointFunction() override;
	virtual float GetDistance() override;
	virtual float GetCurrentDistance() override;
	virtual float GetCuurentVelocity() override;
	virtual float CalculateSplineLength(FVector TrajectoryEnd) override;

	float CurrentDistance = 0.0f;
	float Distance = 0.0f;
};
