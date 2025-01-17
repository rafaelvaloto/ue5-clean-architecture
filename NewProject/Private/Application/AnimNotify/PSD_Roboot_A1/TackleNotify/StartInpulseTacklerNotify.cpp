// Fill out your copyright notice in the Description page of Project Settings.


#include "Application/AnimNotify/PSD_Roboot_A1/TackleNotify/StartInpulseTacklerNotify.h"

#include "Application/PlayerCharacter/PlayerCharacter.h"


void UStartInpulseTacklerNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	// Garante que o MeshComp é válido.
	if (!MeshComp) return;

	APlayerCharacter* Character = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (!Character) return;
	
	UE_LOG(LogTemp, Warning, TEXT("Add impulse %s"), *Character->GetName());
	// Aplicar impulso no personagem usando um vetor (Exemplo: para frente)
	FVector CurrentVelocity = Character->GetVelocity();
	const FVector ImpulseStrength = Character->GetActorForwardVector() * 600.0f; // Ajuste o valor como necessário
	// Início do impulso suave usando interpolação
	// FVector SmoothedImpulse = FMath::VInterpTo(CurrentVelocity, ImpulseStrength, GetWorld()->DeltaTimeSeconds, 0.5f);

	// Aplicar a força suavizada no personagem
	Character->LaunchCharacter(ImpulseStrength, true, true);

	// UE_LOG(LogTemp, Log, TEXT("Smooth Impulse applied: %s"), *SmoothedImpulse.ToString());
}
