// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NewProject/Interfaces/CharacterComponents/UpdateStateCharacterComponentInterface.h"
#include "UpdateStateCharacterComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEWPROJECT_API UUpdateStateCharacterComponent : public UActorComponent, public IUpdateStateCharacterComponentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUpdateStateCharacterComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State Machine")
	EPlayerCharacterState CurrentState = EPlayerCharacterState::Idle;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetCurrentState(EPlayerCharacterState State) override;
	virtual EPlayerCharacterState GetState() override;

	static FText GetStateDisplayName(EPlayerCharacterState State);
};
