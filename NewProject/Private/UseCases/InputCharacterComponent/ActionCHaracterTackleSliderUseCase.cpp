// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/InputCharacterComponent/ActionCHaracterTackleSliderUseCase.h"

void UActionCHaracterTackleSliderUseCase::Handle(
	APlayerCharacter* Character,
	const TScriptInterface<IInputCharacterInterface>& MovementComponent,
	const TScriptInterface<IUpdateStateCharacterComponentInterface>& StateCharacterComponent,
	const TScriptInterface<ISelectorPoseSearchDatabaseInterface>& SelectorPoseSearchDatabase,
	const bool bIsStarted
)
{
	if (bIsStarted)
	{
		SelectorPoseSearchDatabase->SetWaitingNotifyAnim(EWaitingNotifyAnimEnum::Waiting);
		StateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::TackleSlider);
		SelectorPoseSearchDatabase->SetInterruptMode(EPoseSearchInterruptMode::ForceInterrupt);

		UAnimSequence* MyAnimationSequence = LoadObject<UAnimSequence>(nullptr, TEXT("/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/090_AA_Soccer_Player_SlideTackle_R.090_AA_Soccer_Player_SlideTackle_R"));
		if (MyAnimationSequence)
		{
			Character->PlayDynamicMontage(MyAnimationSequence, FName("DefaultSlot"), 0.8f);
		}
		
		return;
	}

	if (StateCharacterComponent->GetState() != EPlayerCharacterStateEnum::TackleSlider)
	{
		return;
	}

	SelectorPoseSearchDatabase->SetWaitingNotifyAnim(EWaitingNotifyAnimEnum::None);
	StateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::Walking);
}
