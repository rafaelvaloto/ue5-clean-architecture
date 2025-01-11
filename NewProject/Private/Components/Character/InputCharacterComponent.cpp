// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Character/InputCharacterComponent.h"

#include "Application/PlayerCharacter/PlayerCharacter.h"
#include "Application/PlayerController/JogPlayerController.h"


// Sets default values for this component's properties
UInputCharacterComponent::UInputCharacterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UInputCharacterComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
}


// Called every frame
void UInputCharacterComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInputCharacterComponent::Move(FVector InputController)
{
	APlayerCharacter* Character = Cast<APlayerCharacter>(GetOwner());
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character not found in UInputCharacterComponent::Move"));
		return;
	}

	AJogPlayerController* Controller = Cast<AJogPlayerController>(Character->GetController());
	if (!Controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controller not found in UInputCharacterComponent::Move"));
		return;
	}

	// Obtém a direção para a frente com base na rotação do controlador
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// Obtém a direção da frente
	const FVector FowardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
	Character->AddMovementInput(FowardDirection, InputController.Y);
	Character->AddMovementInput(RightDirection, -InputController.X);
}

