// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Character/UpdateAttributesCharacterComponent.h"

UUpdateAttributesCharacterComponent::UUpdateAttributesCharacterComponent():
	MagnitudeAcceleration(0.0f),
	bIsDetectedDirectionChange(false)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UUpdateAttributesCharacterComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UUpdateAttributesCharacterComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	CalcMagnitudeAcceleration(DeltaTime);
	DetectDirectionChange(DeltaTime);
	DispatchEvent(DeltaTime);
}


void UUpdateAttributesCharacterComponent::SetVelocityCurrent(const FVector VelocityAt)
{
	if (VelocityAt.Size() <= 0.01f)
	{
		PreviousVelocity = VelocityAt;
		CurrentVelocity = VelocityAt;
		return;
	}

	PreviousVelocity = CurrentVelocity;
	CurrentVelocity = VelocityAt;
}

FVector UUpdateAttributesCharacterComponent::GetComponentActorForwardVector()
{
	return GetOwner()->GetActorForwardVector();
}

void UUpdateAttributesCharacterComponent::DetectDirectionChange(float DeltaTime)
{
	bIsDetectedDirectionChange = false;
	const FVector CurrentDirection = GetVelocityCurrent().GetSafeNormal();
	if (
		!PreviousDirection.IsNearlyZero() &&
		!FVector::PointsAreNear(CurrentDirection, PreviousDirection, 0.01f))
	{
		PreviousDirection = CurrentDirection;
		bIsDetectedDirectionChange = true;
		return;
	}
	PreviousDirection = CurrentDirection;
}

void UUpdateAttributesCharacterComponent::DispatchEvent(float DeltaTime)
{
	const float CurrentSize = GetVelocitySize();
	const float PreviousSize = GetPreviousVelocitySize();
	const float Acceleration = GetMagnitudeAcceleration();
	if (CurrentSize < PreviousSize)
	{
		OnDeceleration.Broadcast(PreviousSize, CurrentSize);
		return;
	}
	OnAcceleration.Broadcast(PreviousSize, CurrentSize, Acceleration);
}

void UUpdateAttributesCharacterComponent::CalcMagnitudeAcceleration(const float DeltaTime)
{
	MagnitudeAcceleration = (GetVelocityCurrent() - GetPreviousVelocity()).Size() / DeltaTime;
}

void UUpdateAttributesCharacterComponent::SetLocationCurrent(const FVector LocationAt)
{
	PreviousLocation = CurrentLocation;
	CurrentLocation = LocationAt;
}

FVector UUpdateAttributesCharacterComponent::GetVelocityCurrent()
{
	return CurrentVelocity;
}

FVector UUpdateAttributesCharacterComponent::GetPreviousVelocity()
{
	return PreviousVelocity;
}

FVector UUpdateAttributesCharacterComponent::GetLocationCurrent()
{
	return CurrentLocation;
}

FVector UUpdateAttributesCharacterComponent::GetPreviousLocation()
{
	return PreviousLocation;
}

float UUpdateAttributesCharacterComponent::GetMagnitudeAcceleration()
{
	return MagnitudeAcceleration;
}

float UUpdateAttributesCharacterComponent::GetVelocitySize()
{
	return CurrentVelocity.Size();
}

float UUpdateAttributesCharacterComponent::GetVelocitySize2D()
{
	return CurrentVelocity.Size2D();
}

bool UUpdateAttributesCharacterComponent::IsDetectedDirectionChange()
{
	return bIsDetectedDirectionChange;
}

float UUpdateAttributesCharacterComponent::GetPreviousVelocitySize()
{
	return PreviousVelocity.Size();
}
