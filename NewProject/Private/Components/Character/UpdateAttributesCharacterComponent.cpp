// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Character/UpdateAttributesCharacterComponent.h"

// Sets default values for this component's properties
UUpdateAttributesCharacterComponent::UUpdateAttributesCharacterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUpdateAttributesCharacterComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UUpdateAttributesCharacterComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                    FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UUpdateAttributesCharacterComponent::SetVelocityCurrent(const FVector VelocityAt)
{
	CurrentVelocity = VelocityAt;
}

FVector UUpdateAttributesCharacterComponent::GetVelocityCurrent()
{
	return CurrentVelocity;
}

float UUpdateAttributesCharacterComponent::GetVelocitySize()
{
	return CurrentVelocity.Size();
}

float UUpdateAttributesCharacterComponent::GetVelocitySize2D()
{
	return CurrentVelocity.Size2D();
}

