// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Character/UpdateAttributesCharacterComponent.h"

#include "Application/PlayerCharacter/PlayerCharacter.h"

// Sets default values for this component's properties
UUpdateAttributesCharacterComponent::UUpdateAttributesCharacterComponent():
	MagnitudeAcceleration(0.0f),
	bIsDetectedDirectionChange(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
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

	CalcMagnitudeAcceleration(DeltaTime);
	DetectDirectionChange(DeltaTime);


	// Despacha os eventos de broadcasts
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


void UUpdateAttributesCharacterComponent::DetectDirectionChange(float DeltaTime)
{
	bIsDetectedDirectionChange = false;
	
	// Obtenha a direção de movimento atual
	const FVector CurrentDirection = GetVelocityCurrent().GetSafeNormal();

	// Verifique se há uma alteração de direção
	if (
		!PreviousDirection.IsNearlyZero() &&
		!FVector::PointsAreNear(CurrentDirection, PreviousDirection, 0.01f))
	{
		UE_LOG(LogTemp, Log, TEXT("Mudança de direção detectada! Direção anterior: %s, Direção atual: %s"),
		       *PreviousDirection.ToString(), *CurrentDirection.ToString());

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Mudou direcao"));
		}

		PreviousDirection = CurrentDirection;
		bIsDetectedDirectionChange = true;
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Mesma direcao"));

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
