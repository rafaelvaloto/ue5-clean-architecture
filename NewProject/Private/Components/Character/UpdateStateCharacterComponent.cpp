// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Character/UpdateStateCharacterComponent.h"


// Sets default values for this component's properties
UUpdateStateCharacterComponent::UUpdateStateCharacterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUpdateStateCharacterComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UUpdateStateCharacterComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UUpdateStateCharacterComponent::SetCurrentState(EPlayerCharacterStateEnum State)
{
	UE_LOG(LogTemp, Warning, TEXT("State[%d]:  %s"), State, *GetStateDisplayName(State).ToString());

	PreviousState = CurrentState;
	CurrentState = State;
	
	// Chama o delegate
	OnStateChanged.Broadcast(CurrentState, PreviousState);
}

EPlayerCharacterStateEnum UUpdateStateCharacterComponent::GetState()
{
	AActor *Actor = GetOwner();
	if (!Actor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor not found in UUpdateStateCharacterComponent::GetState"));
		return EPlayerCharacterStateEnum::Idle;
	}
	
	return CurrentState;
}

FText UUpdateStateCharacterComponent::GetStateDisplayName(EPlayerCharacterStateEnum State)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EPlayerCharacterStateEnum"), true);
	if (!EnumPtr)
	{
		return FText::FromString("Invalid State");
	}

	// Retorna o DisplayName como FText
	return EnumPtr->GetDisplayNameTextByValue(static_cast<uint8>(State));
}