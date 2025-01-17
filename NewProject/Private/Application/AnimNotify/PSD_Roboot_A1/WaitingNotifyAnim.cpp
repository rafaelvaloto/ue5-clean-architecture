// Fill out your copyright notice in the Description page of Project Settings.


#include "Application/AnimNotify/PSD_Roboot_A1/WaitingNotifyAnim.h"

#include "Application/PlayerCharacter/PlayerCharacter.h"

// Lógica executada ao final da animação.
void UWaitingNotifyAnim::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	// Garante que o MeshComp é válido.
	if (!MeshComp) return;

	APlayerCharacter* Character = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (!Character) return;
	
	UE_LOG(LogTemp, Warning, TEXT("Fim da animacao %s"), *Character->GetName());
	Character->SelectorPoseSearchDatabaseComponent->WaitingNotifyAnim = EWaitingNotifyAnimEnum::None;
	if (Character->UpdateStateCharacterComponent->GetPeviousState() == EPlayerCharacterStateEnum::Tackle)
	{
		Character->UpdateStateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::WalkingPivot);
		return;
	}
	Character->UpdateStateCharacterComponent->SetCurrentState(Character->UpdateStateCharacterComponent->GetPeviousState());
}