// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StaticMeshActor/CurrentBallComponent.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UCurrentBallComponent::UCurrentBallComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCurrentBallComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCurrentBallComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

ABallStaticMeshActor* UCurrentBallComponent::CurrentBall()
{
	const UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("World is null. Cannot find BallStaticMeshActor."));
		return nullptr;
	}

	// Retorna o primeiro ABallStaticMeshActor no mundo
	for (TActorIterator<ABallStaticMeshActor> It(World); It; ++It)
	{
		if (ABallStaticMeshActor* BallActor = *It; IsValid(BallActor))
		{
			return BallActor;
		}
	}

	return nullptr;
}

FVector UCurrentBallComponent::GetLocationBall()
{
	const ABallStaticMeshActor* BallActor = CurrentBall();
	if (!BallActor)
	{
		return FVector::ZeroVector;
	}
	
	return BallActor->GetActorLocation();
}

FVector UCurrentBallComponent::GetVelocityBall()
{
	const ABallStaticMeshActor* BallActor = CurrentBall();
	if (!BallActor)
	{
		return FVector::ZeroVector;
	}
	
	return BallActor->GetVelocity();
}
