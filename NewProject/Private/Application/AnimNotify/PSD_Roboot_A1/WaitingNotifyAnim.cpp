// Fill out your copyright notice in the Description page of Project Settings.


#include "Application/AnimNotify/PSD_Roboot_A1/WaitingNotifyAnim.h"

#include "Application/PlayerCharacter/PlayerCharacter.h"

// Lógica executada ao final da animação.
void UWaitingNotifyAnim::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

	UE_LOG(LogTemp, Warning, TEXT("Fim da animacao"));
	
	// Garante que o MeshComp é válido.
	if (!MeshComp) return;

	// Obtém o proprietário do Mesh.
	APlayerCharacter* Owner = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (!Owner) return;

	
	Owner->SelectorPoseSearchDatabaseComponent->WaitingNotifyAnim = EWaitingNotifyAnimEnum::None;
	Owner->UpdateStateCharacterComponent->SetCurrentState(Owner->UpdateStateCharacterComponent->GetPeviousState());
}