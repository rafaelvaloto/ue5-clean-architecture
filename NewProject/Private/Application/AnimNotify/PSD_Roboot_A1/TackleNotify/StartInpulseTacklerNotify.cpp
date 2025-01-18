// Fill out your copyright notice in the Description page of Project Settings.


#include "Application/AnimNotify/PSD_Roboot_A1/TackleNotify/StartInpulseTacklerNotify.h"

#include "Application/PlayerCharacter/PlayerCharacter.h"


void UStartInpulseTacklerNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	// Garante que o MeshComp é válido.
	if (!MeshComp) return;

	APlayerCharacter* Character = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (!Character) return;
	
	Character->StartInpulse = true;
}
