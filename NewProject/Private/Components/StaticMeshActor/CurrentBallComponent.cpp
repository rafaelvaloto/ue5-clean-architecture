// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StaticMeshActor/CurrentBallComponent.h"

#include "Application/BallStaticMeshActor/BallStaticMeshActor.h"


UCurrentBallComponent::UCurrentBallComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

AActor* UCurrentBallComponent::CurrentBall()
{
	return GetOwner();
}

bool UCurrentBallComponent::IsContact()
{
	ABallStaticMeshActor* Ball = Cast<ABallStaticMeshActor>(GetOwner());
	if (!Ball)
	{
		return false;
	}
	
	return Ball->IsContact;
}
