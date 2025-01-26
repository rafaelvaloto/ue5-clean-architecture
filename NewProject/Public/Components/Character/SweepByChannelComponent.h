// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NewProject/Interfaces/CharacterComponents/SweepByChannelComponentInterface.h"
#include "SweepByChannelComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEWPROJECT_API USweepByChannelComponent : public UActorComponent, public ISweepByChannelComponentInterface
{
	GENERATED_BODY()

	bool bIsDebugDrawLines = false;
	FHitResult HitResult;
public:
	// Sets default values for this component's properties
	USweepByChannelComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void DebugDrawLines(bool IsDebug) override;
	virtual bool DetectBallCollision() override;
	virtual FHitResult GetHitResult() override;
};
