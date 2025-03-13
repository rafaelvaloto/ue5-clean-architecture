// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/CharacterControllBall/CharacterControllBallUseCase.h"
#include "Services/CurrentBall/CurrentBallService.h"

void UCharacterControllBallUseCase::Handle(
	const TScriptInterface<ISweepByChannelComponentInterface>& SweepChannel,
	const TScriptInterface<ISelectClosestBoneCharacterComponentInterface>& SelectBoneComponent,
	const TScriptInterface<IUpdateStateCharacterComponentInterface>& StateCharacterComponent,
	const TScriptInterface<IPlayAnimMontageComponentInterface>& PlayAnimMontageComponent,
	const TScriptInterface<ISelectorPoseSearchDatabaseInterface>& SelectorPoseSearchDatabase
)
{
	const bool SweepDetect = SweepChannel->DetectBallCollision();

	if (
		SweepDetect &&
		(
			StateCharacterComponent->GetState() != EPlayerCharacterStateEnum::Controlling &&
			StateCharacterComponent->GetState() != EPlayerCharacterStateEnum::ControllingTrajectoryChange &&
			StateCharacterComponent->GetState() != EPlayerCharacterStateEnum::Tackle &&
			StateCharacterComponent->GetState() != EPlayerCharacterStateEnum::TackleSlider
		)
	)
	{
		if (SelectorPoseSearchDatabase->GetInterruptMode() != EPoseSearchInterruptMode::ForceInterrupt)
		{
			SelectorPoseSearchDatabase->SetInterruptMode(EPoseSearchInterruptMode::ForceInterrupt);
		}

		StateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::Controlling);

		ESelectClosestBoneCharacterEnum DefineBoneAnim = SelectBoneComponent->SelectClosestFootBoneToBall(
			UCurrentBallService::CurrentBall());

		SelectBoneComponent->SetFoot(DefineBoneAnim);
		if (DefineBoneAnim == ESelectClosestBoneCharacterEnum::LeftFoot)
		{
			UAnimSequence* AnimSeq = LoadObject<UAnimSequence>(
				nullptr,
				TEXT(
					"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/095_AA_Soccer_Player_DribbleF_L.095_AA_Soccer_Player_DribbleF_L"
				)
			);

			if (!AnimSeq)
			{
				return;
			}

			PlayAnimMontageComponent->PlayDynamicMontage(AnimSeq, FName("DefaultSlot"), 0.8f, 0.0f,
			                                             0.0f, true);
			return;
		}


		UAnimSequence* AnimSeq = LoadObject<UAnimSequence>(
			nullptr,
			TEXT(
				"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/094_AA_Soccer_Player_DribbleF_R.094_AA_Soccer_Player_DribbleF_R"
			)
		);

		if (!AnimSeq)
		{
			return;
		}

		PlayAnimMontageComponent->PlayDynamicMontage(AnimSeq, FName("DefaultSlot"), 0.8f, 0.0f,
		                                             0.0f, true);
		return;
	}

	if (
		!SweepDetect &&
		(
			StateCharacterComponent->GetState() == EPlayerCharacterStateEnum::Controlling ||
			StateCharacterComponent->GetState() == EPlayerCharacterStateEnum::ControllingTrajectoryChange
		)
	)
	{
		UE_LOG(LogTemp, Error, TEXT("Stop Controlling"));
		PlayAnimMontageComponent->StopDynamicMontage();
		StateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::Idle);
		SelectorPoseSearchDatabase->SetInterruptMode(EPoseSearchInterruptMode::DoNotInterrupt);
	}
}
