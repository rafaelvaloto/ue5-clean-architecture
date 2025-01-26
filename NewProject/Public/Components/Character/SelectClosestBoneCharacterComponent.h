﻿// Fill out your copyright notice in the Description page of Project Settings.

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
	USelectClosestBoneCharacterComponent();

	virtual ESelectClosestBoneCharacterEnum SelectClosestFootBoneToBall(AActor* BallActor) override;
};
