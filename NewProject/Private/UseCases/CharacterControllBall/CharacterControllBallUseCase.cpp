// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/CharacterControllBall/CharacterControllBallUseCase.h"
#include "Services/CurrentBall/CurrentBallService.h"

void UCharacterControllBallUseCase::Handle(
		const TScriptInterface<ISweepByChannelComponentInterface>& SweepByChannel,
		const TScriptInterface<ISelectClosestBoneCharacterComponentInterface>& SelectBoneComponent,
		const TScriptInterface<IPlayAnimMontageComponentInterface>& PlayAnimMontageComponent,
		const TScriptInterface<ISelectorPoseSearchDatabaseInterface>& SelectorPoseSearchDatabase
		)
{
	if (SweepByChannel->DetectBallCollision())
	{
		ESelectClosestBoneCharacterEnum DefineBoneAnim = SelectBoneComponent->SelectClosestFootBoneToBall(UCurrentBallService::CurrentBall());

		SelectorPoseSearchDatabase->SetInterruptMode(EPoseSearchInterruptMode::ForceInterrupt);
		if (DefineBoneAnim == ESelectClosestBoneCharacterEnum::LeftFoot)
		{
			UAnimSequence* MyAnimationSequence = LoadObject<UAnimSequence>(
				nullptr, TEXT(
					"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/095_AA_Soccer_Player_DribbleF_L.095_AA_Soccer_Player_DribbleF_L"
				));
			if (MyAnimationSequence)
			{
				PlayAnimMontageComponent->PlayDynamicMontage(MyAnimationSequence, FName("DefaultSlot"), 0.8f, 0.0f, 0.0f, true);
				return;
			}
		}

		UAnimSequence* MyAnimationSequence = LoadObject<UAnimSequence>(
			nullptr, TEXT(
				"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/094_AA_Soccer_Player_DribbleF_R.094_AA_Soccer_Player_DribbleF_R"
			));
		if (MyAnimationSequence)
		{
			PlayAnimMontageComponent->PlayDynamicMontage(MyAnimationSequence, FName("DefaultSlot"), 0.8f, 0.0f, 0.0f, true);
		}
	}
}
