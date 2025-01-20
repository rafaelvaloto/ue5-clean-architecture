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

		TArray<UAnimSequence*> Animations = TArray<UAnimSequence*>();


		SelectorPoseSearchDatabase->SetWaitingNotifyAnim(EWaitingNotifyAnimEnum::Waiting);
		StateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::Tackle);
		SelectorPoseSearchDatabase->SetInterruptMode(EPoseSearchInterruptMode::ForceInterrupt);

		if (DefineBoneAnim == ESelectClosestBoneCharacterEnum::LeftFoot)
		{
			Animations.Add(LoadObject<UAnimSequence>(
				nullptr, TEXT(
					"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/091_AA_Soccer_Player_SlideTackle_L.091_AA_Soccer_Player_SlideTackle_L")));

			Animations.Add(
				LoadObject<UAnimSequence>(
					nullptr, TEXT(
					"/Game/Characters/UEFN_Mannequin/Animations/Idle/M_Neutral_Stand_Turn_045_L.M_Neutral_Stand_Turn_045_L")
				)
			);
			PlayAnimMontageComponent->SetDynamicMontages(Animations, FName("DefaultSlot"), 1.0f);
			return;
		}

		Animations.Add(LoadObject<UAnimSequence>
			(
				nullptr, TEXT(
					"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/090_AA_Soccer_Player_SlideTackle_R.090_AA_Soccer_Player_SlideTackle_R")
			)
		);
		
		Animations.Add(
			LoadObject<UAnimSequence>(
				nullptr, TEXT(
					"/Game/Characters/UEFN_Mannequin/Animations/Idle/M_Neutral_Stand_Turn_045_L.M_Neutral_Stand_Turn_045_L")
			)
		);
		PlayAnimMontageComponent->SetDynamicMontages(Animations, FName("DefaultSlot"), 1.0f);
		return;
	}

	if (StateCharacterComponent->GetState() != EPlayerCharacterStateEnum::TackleSlider)
	{
		return;
	}

	StateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::Idle);
	SelectorPoseSearchDatabase->SetInterruptMode(EPoseSearchInterruptMode::DoNotInterrupt);
	SelectorPoseSearchDatabase->SetWaitingNotifyAnim(EWaitingNotifyAnimEnum::None);
}
