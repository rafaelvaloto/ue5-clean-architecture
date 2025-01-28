// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Character/InputCharacterComponent.h"

#include "Application/PlayerCharacter/PlayerCharacter.h"
#include "Application/PlayerController/JogPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UseCases/UpdateStateCharacterComponent/UpdateStateCharacterComponentUseCase.h"


// Sets default values for this component's properties
UInputCharacterComponent::UInputCharacterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInputCharacterComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInputCharacterComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInputCharacterComponent::SetBlockMove(const bool bIsBlocked)
{
	bIsBlockMove = bIsBlocked;
}

bool UInputCharacterComponent::GetBlockMove()
{
	return bIsBlockMove;
}

void UInputCharacterComponent::NormalizeCharacterAfterGetUp()
{
	APlayerCharacter* Character = Cast<APlayerCharacter>(GetOwner());
	if (!Character)
	{
		return;
	}

	// Garantir que o Capsule Component está configurado corretamente
	Character->GetCapsuleComponent()->SetHiddenInGame(false);
	Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    
	// Ajustar orientação do personagem para o padrão:
	Character->GetCharacterMovement()->bOrientRotationToMovement = true;
	Character->GetCharacterMovement()->bUseControllerDesiredRotation = false;

	// Garantir que velocidades e forças estão padrão
	Character->GetCharacterMovement()->StopMovementImmediately();
}

void UInputCharacterComponent::ControlYaw(const float InputValue)
{
	if (const APlayerCharacter* Character = Cast<APlayerCharacter>(GetOwner()); !Character)
	{
		return;
	}

	SetOrientRotationToMovement(InputValue <= 0.0f);
}

void UInputCharacterComponent::Move(FVector InputController)
{
	APlayerCharacter* Character = Cast<APlayerCharacter>(GetOwner());
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character not found in UInputCharacterComponent::Move"));
		return;
	}

	const AJogPlayerController* Controller = Cast<AJogPlayerController>(Character->GetController());
	if (!Controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controller not found in UInputCharacterComponent::Move"));
		return;
	}
	
	// Mantém o movimento independente do estado atual de bIsMovingControlYaw.
	const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);

	// Consistência nas direções da frente e lateral.
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // Frente
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);  // Direita
	
	// Aplica Input de movimento sem inversões.
	Character->AddMovementInput(ForwardDirection, -InputController.Y);
	Character->AddMovementInput(RightDirection, -InputController.X);
	Character->LastPosition  = FVector(InputController.X, -InputController.Y, 0.0f);
}

void UInputCharacterComponent::ResetRotationForController() const
{
	// Pega o personagem dono deste componente.
	const APlayerCharacter* Character = Cast<APlayerCharacter>(GetOwner());
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character not found in UInputCharacterComponent::ResetRotationForController"));
		return;
	}

	// Pega o controlador associado ao personagem.
	APlayerController* Controller = Cast<APlayerController>(Character->GetController());
	if (!Controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controller not found in UInputCharacterComponent::ResetRotationForController"));
		return;
	}

	const FRotator DesiredRotation = Controller->GetDesiredRotation();

	// Atualiza o ControlRotation com a DesiredRotation.
	FRotator NewControlRotation = Controller->GetControlRotation();
	NewControlRotation.Yaw = DesiredRotation.Yaw; // Alinha somente o Yaw.
	Controller->SetControlRotation(NewControlRotation);
}

void UInputCharacterComponent::SetOrientRotationToMovement(const bool bNewOrientRotationToMovement) const
{
	const APlayerCharacter* Character = Cast<APlayerCharacter>(GetOwner());
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character not found in UInputCharacterComponent::SetOrientRotationToMovement"));
		return;
	}

	// Pega o movimento do personagem.
	UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
	if (!MovementComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Movement component not found in SetOrientRotationToMovement"));
		return;
	}

	// Atualiza o estado de orientação para movimento.
	MovementComponent->bOrientRotationToMovement = bNewOrientRotationToMovement;

	if (!bNewOrientRotationToMovement)
	{
		// Se desligar OrientRotationToMovement, reseta o ControlRotation para alinhar com a malha.
		ResetRotationForController();
	}
}
