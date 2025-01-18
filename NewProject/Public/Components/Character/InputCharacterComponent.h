// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NewProject/Interfaces/CharacterComponents/InputCharacterInterface.h"
#include "InputCharacterComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEWPROJECT_API UInputCharacterComponent : public UActorComponent, public IInputCharacterInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInputCharacterComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void ResetRotationForController() const;
	void SetOrientRotationToMovement(bool bNewOrientRotationToMovement) const;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Move(FVector InputController) override;
	virtual void ControlYaw(const float InputValue) override;
	virtual void SetBlockMove(const bool bIsBlocked) override;
	virtual bool GetBlockMove() override;

private:
	bool bIsBlockMove = false;
};
