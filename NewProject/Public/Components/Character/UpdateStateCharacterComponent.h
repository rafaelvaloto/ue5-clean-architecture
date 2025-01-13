// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NewProject/Enums/CharacterStates/PlayerCharacterStateEnum.h"
#include "NewProject/Interfaces/CharacterComponents/UpdateStateCharacterComponentInterface.h"
#include "UpdateStateCharacterComponent.generated.h"

// Defina o tipo de delegate (com parâmetros para o estado, se necessário)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStateChanged, EPlayerCharacterStateEnum, NewState, EPlayerCharacterStateEnum, PreviousState);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEWPROJECT_API UUpdateStateCharacterComponent : public UActorComponent, public IUpdateStateCharacterComponentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUpdateStateCharacterComponent();

	// Delegate multicast que outros componentes podem ouvir
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	FOnStateChanged OnStateChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State Machine")
	EPlayerCharacterStateEnum CurrentState = EPlayerCharacterStateEnum::Idle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State Machine")
	EPlayerCharacterStateEnum PreviousState = EPlayerCharacterStateEnum::Idle;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetCurrentState(EPlayerCharacterStateEnum State) override;
	virtual EPlayerCharacterStateEnum GetState() override;
	virtual EPlayerCharacterStateEnum GetPeviousState() override;

	static FText GetStateDisplayName(EPlayerCharacterStateEnum State);
};
