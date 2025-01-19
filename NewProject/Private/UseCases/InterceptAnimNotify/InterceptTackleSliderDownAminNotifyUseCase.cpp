// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/InterceptAnimNotify/InterceptTackleSliderDownAminNotifyUseCase.h"

void UInterceptTackleSliderDownAminNotifyUseCase::Handle(
	TScriptInterface<ICurrentBallComponentInterface> CurrentBallComponent,
	TScriptInterface<IPlayAnimMontageComponentInterface> PlayAnimMontageComponent
)
{
	// todo: escrever regra para selecionar o index da proxima animacao com base no que correu apos a primeira animacao ter terminado
}
