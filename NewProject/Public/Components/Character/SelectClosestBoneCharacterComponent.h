// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NewProject/Interfaces/CharacterComponents/SelectClosestBoneCharacterComponentInterface.h"
#include "SelectClosestBoneCharacterComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEWPROJECT_API USelectClosestBoneCharacterComponent : public UActorComponent, public ISelectClosestBoneCharacterComponentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USelectClosestBoneCharacterComponent();

	virtual ESelectClosestBoneCharacterEnum SelectClosestFootBoneToBall(ABallStaticMeshActor* BallActor) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
