// Fill out your copyright notice in the Description page of Project Settings.


#include "Application/AnimNotify/PSD_Roboot_A1/TackleNotify/TackleSliderDownAminNotify.h"

#include "Application/PlayerCharacter/PlayerCharacter.h"
#include "UseCases/InterceptAnimNotify/InterceptTackleSliderDownAminNotifyUseCase.h"

void UTackleSliderDownAminNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	// Garante que o MeshComp é válido.
	if (!MeshComp) return;

	APlayerCharacter* Character = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (!Character) return;

	UInterceptTackleSliderDownAminNotifyUseCase::Handle(
		Character->PlayAnimMontageComponent,
		Character->MovementPlayerCharacter,
		Character->UpdateStateCharacterComponent,
		Character->UpdatedBaseAttributesComponent,
		Character->SelectorPoseSearchDatabaseComponent
	);
}
