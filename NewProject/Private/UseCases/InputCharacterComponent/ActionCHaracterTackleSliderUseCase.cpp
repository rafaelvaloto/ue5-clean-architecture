// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/InputCharacterComponent/ActionCHaracterTackleSliderUseCase.h"

void UActionCHaracterTackleSliderUseCase::Handle(
	const TScriptInterface<ICurrentBallComponentInterface> CurrentBallComponent,
	const TScriptInterface<ISelectClosestBoneCharacterComponentInterface> SelectBoneComponent,
	const TScriptInterface<IPlayAnimMontageComponentInterface> PlayAnimMontageComponent,
	const TScriptInterface<IUpdateStateCharacterComponentInterface>& StateCharacterComponent,
	const TScriptInterface<ISelectorPoseSearchDatabaseInterface>& SelectorPoseSearchDatabase,
	const bool bIsStarted
)
{
	if (bIsStarted)
	{
		const ESelectClosestBoneCharacterEnum DefineBoneAnim = SelectBoneComponent->SelectClosestFootBoneToBall(
			CurrentBallComponent->CurrentBall());

		SelectorPoseSearchDatabase->SetWaitingNotifyAnim(EWaitingNotifyAnimEnum::Waiting);
		StateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::TackleSlider);
		SelectorPoseSearchDatabase->SetInterruptMode(EPoseSearchInterruptMode::ForceInterrupt);

		if (DefineBoneAnim == ESelectClosestBoneCharacterEnum::LeftFoot)
		{
			UAnimSequence* MyAnimationSequence = LoadObject<UAnimSequence>(
				nullptr, TEXT(
					"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/091_AA_Soccer_Player_SlideTackle_L.091_AA_Soccer_Player_SlideTackle_L"));
			if (MyAnimationSequence)
			{
				PlayAnimMontageComponent->PlayDynamicMontage(MyAnimationSequence, FName("DefaultSlot"), 0.8f);
				return;
			}
		}

		UAnimSequence* MyAnimationSequence = LoadObject<UAnimSequence>(
			nullptr, TEXT(
				"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/090_AA_Soccer_Player_SlideTackle_R.090_AA_Soccer_Player_SlideTackle_R"));
		if (MyAnimationSequence)
		{
			PlayAnimMontageComponent->PlayDynamicMontage(MyAnimationSequence, FName("DefaultSlot"), 0.8f);
		}

		return;
	}

	if (StateCharacterComponent->GetState() != EPlayerCharacterStateEnum::TackleSlider)
	{
		return;
	}

	SelectorPoseSearchDatabase->SetWaitingNotifyAnim(EWaitingNotifyAnimEnum::None);
	StateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::Idle);
}
