// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/InterceptAnimNotify/InterceptTackleSliderDownAminNotifyUseCase.h"

#include "NewProject/Interfaces/CharacterComponents/UpdateAttributesCharacterComponentInterface.h"
#include "NewProject/Interfaces/MotionMatchHelpersComponents/SelectorPoseSearchDatabaseInterface.h"

void UInterceptTackleSliderDownAminNotifyUseCase::Handle(
	TScriptInterface<ICurrentBallComponentInterface> CurrentBallComponent,
	TScriptInterface<IPlayAnimMontageComponentInterface> PlayAnimMontageComponent,
	TScriptInterface<IInputCharacterInterface> InputCharacterComponent,
	TScriptInterface<IUpdateStateCharacterComponentInterface> StateCharacterComponent,
	TScriptInterface<IUpdateAttributesCharacterComponentInterface> AttributesCharacterComponent,
	TScriptInterface<ISelectorPoseSearchDatabaseInterface> SelectorPoseSearchDatabase
)
{
	UE_LOG(LogTemp, Warning, TEXT("InterceptTackleSliderDownAminNotifyUseCase"));
	InputCharacterComponent->NormalizeCharacterAfterGetUp();
	SelectorPoseSearchDatabase->SetInterruptMode(EPoseSearchInterruptMode::DoNotInterrupt);
	AttributesCharacterComponent->SetVelocityCurrent(FVector::ZeroVector);
	StateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::Running);
	// PlayAnimMontageComponent->DefineIndexPlayDynamicMontage(1, FName("DefaultSlot"), 2.0f);
}
