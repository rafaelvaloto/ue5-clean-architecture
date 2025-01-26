// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/InterceptAnimNotify/InterceptTackleSliderDownAminNotifyUseCase.h"

#include "NewProject/Interfaces/CharacterComponents/UpdateAttributesCharacterComponentInterface.h"
#include "NewProject/Interfaces/MotionMatchHelpersComponents/SelectorPoseSearchDatabaseInterface.h"

void UInterceptTackleSliderDownAminNotifyUseCase::Handle(
	TScriptInterface<IPlayAnimMontageComponentInterface> PlayAnimMontageComponent,
	TScriptInterface<IInputCharacterInterface> InputCharacterComponent,
	TScriptInterface<IUpdateStateCharacterComponentInterface> StateCharacterComponent,
	TScriptInterface<IUpdateAttributesCharacterComponentInterface> AttributesCharacterComponent,
	TScriptInterface<ISelectorPoseSearchDatabaseInterface> SelectorPoseSearchDatabase
)
{
	InputCharacterComponent->NormalizeCharacterAfterGetUp();
	SelectorPoseSearchDatabase->SetInterruptMode(EPoseSearchInterruptMode::DoNotInterrupt);
	StateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::Idle);
}
