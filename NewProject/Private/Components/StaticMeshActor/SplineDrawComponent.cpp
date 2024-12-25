// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StaticMeshActor/SplineDrawComponent.h"
#include "Application/BallStaticMeshActor/BallStaticMeshActor.h"

// Sets default values for this component's properties
USplineDrawComponent::USplineDrawComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USplineDrawComponent::AddSplinePointFunction()
{
	if (!GetOwner())
	{
		UE_LOG(LogTemp, Warning, TEXT("GetOwner not found in USplineDrawComponent::AddSplinePointFunction"));
		return;
	}
	
	FVector Start = FVector(GetOwner()->GetActorLocation().X, GetOwner()->GetActorLocation().Y, 24.f);
	FVector End = Start + Start.GetSafeNormal() * Distance;
	
	// Desenhe a trajetória usando Debug Draw
	DrawDebugLine(GetWorld(), Start, FVector(End.X, End.Y, 24.f), FColor::Green, true, 1.f, SDPG_World, 4.f);
	DrawDebugPoint(GetWorld(), Start, 10.f, FColor::Blue, true);
	DrawDebugPoint(GetWorld(), FVector(End.X, End.Y, 24.f), 10.f, FColor::Blue, true);
}

void USplineDrawComponent::SetComponentVelocity(FVector Velocity)
{
	AStaticMeshActor* Actor = Cast<AStaticMeshActor>(GetOwner());
	if (!Actor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor not found in USplineDrawComponent::SetComponentVelocity"));
		return;
	}
	
	Actor->GetStaticMeshComponent()->SetPhysicsLinearVelocity(FVector(Velocity.X, Velocity.Y, 22.5f));
}

float USplineDrawComponent::CalculateSplineLength(FVector TrajectoryEnd)
{
	AStaticMeshActor* Actor = Cast<AStaticMeshActor>(GetOwner());
	if (!Actor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor not found in USplineDrawComponent::CalculateSplineLength"));
		return 0.f;
	}
	
	FVector Start = FVector(GetOwner()->GetActorLocation().X, GetOwner()->GetActorLocation().Y, 0.f);
	return FVector::Distance(Start, TrajectoryEnd);
}

float USplineDrawComponent::GetDistance()
{
	return Distance;
}

float USplineDrawComponent::GetCurrentDistance()
{
	return CurrentDistance;
}

float USplineDrawComponent::GetCuurentVelocity()
{
	return GetOwner()->GetVelocity().Size2D();
}

void USplineDrawComponent::SetCurrentDistance(float Value)
{
	CurrentDistance = Value;
}

void USplineDrawComponent::SetDistance(float Value)
{
	Distance = Value;
}
