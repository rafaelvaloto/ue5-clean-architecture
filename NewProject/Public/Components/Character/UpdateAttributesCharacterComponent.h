// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NewProject/Interfaces/CharacterComponents/UpdateAttributesCharacterComponentInterface.h"
#include "UpdateAttributesCharacterComponent.generated.h"

// Defina o tipo de delegate (com parâmetros na desaceleracao)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDeceleration, float, PrevVelocity, float, Velocity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAcceleration, float, PrevVelocity, float, Velocity, float, Acceleration);

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

	virtual void SetLocationCurrent(const FVector LocationAt) override;
	virtual void SetVelocityCurrent(const FVector VelocityAt) override;
	
	virtual FVector GetVelocityCurrent() override;
	virtual FVector GetPreviousVelocity() override;
	virtual FVector GetLocationCurrent() override;
	virtual FVector GetPreviousLocation() override;
	virtual float GetMagnitudeAcceleration() override;

	virtual float GetVelocitySize() override;
	virtual float GetVelocitySize2D() override;
	virtual float GetPreviousVelocitySize() override;

	virtual void DetectDirectionChange(float DeltaTime) override;
	virtual bool IsDetectedDirectionChange() override;
	
	virtual void DispatchEvent(float DeltaTime);
	virtual void CalcMagnitudeAcceleration(float DeltaTime);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Velocity")
	FOnDeceleration OnDeceleration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Velocity")
	FOnAcceleration OnAcceleration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Velocity")
	FVector CurrentVelocity = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Velocity")
	FVector PreviousVelocity = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Location")
	FVector CurrentLocation = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Location")
	FVector PreviousLocation = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Velocity")
	float MagnitudeAcceleration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Direction")
	FVector PreviousDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Direction")
	bool bIsDetectedDirectionChange;
};
