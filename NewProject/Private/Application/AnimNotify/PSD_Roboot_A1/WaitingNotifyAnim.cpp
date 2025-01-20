// Fill out your copyright notice in the Description page of Project Settings.

#include "Application/AnimNotify/PSD_Roboot_A1/WaitingNotifyAnim.h"
#include "Application/PlayerCharacter/PlayerCharacter.h"
#include "UseCases/InputCharacterComponent/ActionCHaracterTackleSliderUseCase.h"
#include "UseCases/InputCharacterComponent/ActionCharacterTackleUseCase.h"

// Lógica executada ao final da animação.
void UWaitingNotifyAnim::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	// Garante que o MeshComp é válido.
	if (!MeshComp) return;

	APlayerCharacter* Character = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (!Character) return;
	
	UActionCharacterTackleUseCase::Handle(
	Character->BallActive,
	Character->ClosestBone,
	Character->PlayAnimMontageComponent,
	Character->UpdateStateCharacterComponent,
	Character->SelectorPoseSearchDatabaseComponent,
		false
	);

	UActionCHaracterTackleSliderUseCase::Handle(
		Character->BallActive,
		Character->ClosestBone,
		Character->PlayAnimMontageComponent,
		Character->UpdateStateCharacterComponent,
		Character->SelectorPoseSearchDatabaseComponent,
		false
	);

	Character->StartInpulse = false;
}
