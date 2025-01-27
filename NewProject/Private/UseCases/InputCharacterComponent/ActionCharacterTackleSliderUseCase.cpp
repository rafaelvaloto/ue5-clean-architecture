// Fill out your copyright notice in the Description page of Project Settings.

#include "UseCases/InputCharacterComponent/ActionCharacterTackleSliderUseCase.h"
#include "Services/CurrentBall/CurrentBallService.h"

void UActionCharacterTackleSliderUseCase::Handle(
	const TScriptInterface<ISelectClosestBoneCharacterComponentInterface>& SelectBoneComponent,
	const TScriptInterface<IPlayAnimMontageComponentInterface>& PlayAnimMontageComponent,
	const TScriptInterface<IUpdateStateCharacterComponentInterface>& StateCharacterComponent,
	const TScriptInterface<ISelectorPoseSearchDatabaseInterface>& SelectorPoseSearchDatabase,
	const bool bIsStarted
)
{
	if (bIsStarted && StateCharacterComponent->GetState() != EPlayerCharacterStateEnum::TackleSlider)
	{

		const ESelectClosestBoneCharacterEnum DefineBoneAnim =
			SelectBoneComponent->SelectClosestFootBoneToBall(UCurrentBallService::CurrentBall());

		TArray<UAnimSequence*> Animations = TArray<UAnimSequence*>();

		StateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::TackleSlider);
		SelectorPoseSearchDatabase->SetInterruptMode(EPoseSearchInterruptMode::ForceInterrupt);

		if (DefineBoneAnim == ESelectClosestBoneCharacterEnum::LeftFoot)
		{
			Animations.Add(LoadObject<UAnimSequence>(
				nullptr, TEXT(
					"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/091_AA_Soccer_Player_SlideTackle_L.091_AA_Soccer_Player_SlideTackle_L")));

			Animations.Add(
				LoadObject<UAnimSequence>(
					nullptr, TEXT(
						"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/024_AA_Soccer_Player_CIdle_R.024_AA_Soccer_Player_CIdle_R")
				)
			);
			PlayAnimMontageComponent->SetDynamicMontages(Animations, FName("DefaultSlot"), 1.0f, 2.0f, 1.23f, false);
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
					"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/024_AA_Soccer_Player_CIdle_R.024_AA_Soccer_Player_CIdle_R")
			)
		);
		PlayAnimMontageComponent->SetDynamicMontages(Animations, FName("DefaultSlot"), 1.0f, 2.0f, 1.23f, false);
	}
}
