// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterTrajectoryComponent.h"
#include "NewProject/Interfaces/CharacterComponents/UpdateTrajectoryCharacterComponentInterface.h"
#include "UpdateTrajectoryCharacterComponent.generated.h"


UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent), Experimental)
class NEWPROJECT_API UUpdateTrajectoryCharacterComponent : public UCharacterTrajectoryComponent, public IUpdateTrajectoryCharacterComponentInterface 
{
	GENERATED_BODY()

public:
	UUpdateTrajectoryCharacterComponent(const FObjectInitializer& ObjectInitializer);
	
	virtual void OnMovementUpdated(float DeltaSeconds, FVector OldLocation, FVector OldVelocity) override;
};
