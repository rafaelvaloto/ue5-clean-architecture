// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/InterceptAnimNotify/InterceptTackleSliderDownAminNotifyUseCase.h"

void UInterceptTackleSliderDownAminNotifyUseCase::Handle(
	TScriptInterface<ICurrentBallComponentInterface> CurrentBallComponent,
	TScriptInterface<IPlayAnimMontageComponentInterface> PlayAnimMontageComponent,
	TScriptInterface<IInputCharacterInterface> InputCharacterComponent
)
{
	UE_LOG(LogTemp, Warning, TEXT("InterceptTackleSliderDownAminNotifyUseCase"));

	InputCharacterComponent->RecoverFromRagdoll();
	InputCharacterComponent->AlignWithMovementInput();
	PlayAnimMontageComponent->DefineIndexPlayDynamicMontage(1);
}
