// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NewProject/Interfaces/CharacterComponents/UpdateAttributesCharacterComponentInterface.h"
#include "UpdateAttributesCharacterComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEWPROJECT_API UUpdateAttributesCharacterComponent : public UActorComponent, public IUpdateAttributesCharacterComponentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUpdateAttributesCharacterComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetVelocityCurrent(const FVector VelocityAt) override;
	virtual FVector GetVelocityCurrent() override;

	virtual float GetVelocitySize() override;
	virtual float GetVelocitySize2D() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Velocity")
	FVector CurrentVelocity = FVector::ZeroVector;
};
