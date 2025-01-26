// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StaticMeshActor/CurrentBallComponent.h"
#include "Engine/World.h"


UCurrentBallComponent::UCurrentBallComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

AActor* UCurrentBallComponent::CurrentBall()
{
	return GetOwner();
}
