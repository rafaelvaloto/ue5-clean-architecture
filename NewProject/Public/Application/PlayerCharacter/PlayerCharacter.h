// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/Character/InputCharacterComponent.h"
#include "Components/Character/UpdateAttributesCharacterComponent.h"
#include "Components/Character/UpdateStateCharacterComponent.h"
#include "Components/Character/UpdateTrajectoryCharacterComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCharacter.generated.h"



UCLASS()
class NEWPROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Functions
private:
	void SetupComponents();
	void SetupSkeletonMesh() const;
	void SetupCameraComponents();
	void SetupAnimInstanceBlueprint() const;

	// Components And Variables
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ICustomMovementComponent")
	UInputCharacterComponent* MovementPlayerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IUpdatedBaseAttributesComponentInterface")
	UUpdateAttributesCharacterComponent* UpdatedBaseAttributesComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IUUpdateStateCharacterComponent")
	UUpdateStateCharacterComponent* UpdateStateCharacterComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TrajectoryComponent")
	UUpdateTrajectoryCharacterComponent* TrajectoryComponent;
};
