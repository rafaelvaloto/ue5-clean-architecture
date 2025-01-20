// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/InputCharacterComponent/ActionCharacterTackleUseCase.h"
#include "NewProject/Enums/PoseSearchDatabaseModeStates/WaitingNotifyAnimEnum.h"

void UActionCharacterTackleUseCase::Handle(
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
					"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/077_AA_Soccer_Player_Tackle_L.077_AA_Soccer_Player_Tackle_L"
				));
			if (MyAnimationSequence)
			{
				PlayAnimMontageComponent->PlayDynamicMontage(MyAnimationSequence, FName("DefaultSlot"), 0.8f);
				return;
			}
		}

		UAnimSequence* MyAnimationSequence = LoadObject<UAnimSequence>(
			nullptr, TEXT(
				"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/076_AA_Soccer_Player_Tackle_R.076_AA_Soccer_Player_Tackle_R"
			));
		if (MyAnimationSequence)
		{
			PlayAnimMontageComponent->PlayDynamicMontage(MyAnimationSequence, FName("DefaultSlot"), 0.8f);
		}

		return;
	}

	if (StateCharacterComponent->GetState() != EPlayerCharacterStateEnum::Tackle)
	{
		return;
	}

	if (StateCharacterComponent->GetPeviousState() == EPlayerCharacterStateEnum::Tackle)
	{
		StateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::Idle);
		SelectorPoseSearchDatabase->SetInterruptMode(EPoseSearchInterruptMode::DoNotInterrupt);
		SelectorPoseSearchDatabase->SetWaitingNotifyAnim(EWaitingNotifyAnimEnum::None);
		return;
	}

	StateCharacterComponent->SetCurrentState(StateCharacterComponent->GetPeviousState());
	SelectorPoseSearchDatabase->SetInterruptMode(EPoseSearchInterruptMode::DoNotInterrupt);
	SelectorPoseSearchDatabase->SetWaitingNotifyAnim(EWaitingNotifyAnimEnum::None);
}
