// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PlayerCharacter/MovementCharacterComponent.h"


// Sets default values for this component's properties
UMovementCharacterComponent::UMovementCharacterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UMovementCharacterComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMovementCharacterComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMovementCharacterComponent::Move(FVector InputController)
{
	// Implemente a movimentação aqui, Character
	UE_LOG(LogTemp, Warning, TEXT("Movement component, %s"), *InputController.ToString());
}

