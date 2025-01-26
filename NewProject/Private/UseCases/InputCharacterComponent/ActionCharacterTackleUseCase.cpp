// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/InputCharacterComponent/ActionCharacterTackleUseCase.h"
#include "Services/CurrentBall/CurrentBallService.h"

void UActionCharacterTackleUseCase::Handle(
	const TScriptInterface<ISelectClosestBoneCharacterComponentInterface>& SelectBoneComponent,
	const TScriptInterface<IPlayAnimMontageComponentInterface>& PlayAnimMontageComponent,
	const TScriptInterface<IUpdateStateCharacterComponentInterface>& StateCharacterComponent,
	const TScriptInterface<ISelectorPoseSearchDatabaseInterface>& SelectorPoseSearchDatabase,
	const bool bIsStarted
)
{
	if (bIsStarted)
	{
		const ESelectClosestBoneCharacterEnum DefineBoneAnim =
			SelectBoneComponent->SelectClosestFootBoneToBall(UCurrentBallService::CurrentBall());

		StateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::Tackle);
		SelectorPoseSearchDatabase->SetInterruptMode(EPoseSearchInterruptMode::ForceInterrupt);

		if (DefineBoneAnim == ESelectClosestBoneCharacterEnum::LeftFoot)
		{
			UAnimSequence* MyAnimationSequence = LoadObject<UAnimSequence>(
				nullptr, TEXT(
					"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/077_AA_Soccer_Player_Tackle_L.077_AA_Soccer_Player_Tackle_L"
				));
			if (MyAnimationSequence)
			{
				PlayAnimMontageComponent->PlayDynamicMontage(MyAnimationSequence, FName("DefaultSlot"), 0.8f, 0.0f, 0.0f, false);
				return;
			}
		}

		UAnimSequence* MyAnimationSequence = LoadObject<UAnimSequence>(
			nullptr, TEXT(
				"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/076_AA_Soccer_Player_Tackle_R.076_AA_Soccer_Player_Tackle_R"
			));
		if (MyAnimationSequence)
		{
			PlayAnimMontageComponent->PlayDynamicMontage(MyAnimationSequence, FName("DefaultSlot"), 0.8f, 0.0f, 0.0f, false);
		}

		return;
	}

	if (StateCharacterComponent->GetState() != EPlayerCharacterStateEnum::Tackle)
	{
		UE_LOG(LogTemp, Warning, TEXT("StateCharacterComponent->GetState() != EPlayerCharacterStateEnum::Tackle"));
		return;
	}

	if (StateCharacterComponent->GetPeviousState() == EPlayerCharacterStateEnum::Tackle)
	{
		SelectorPoseSearchDatabase->SetInterruptMode(EPoseSearchInterruptMode::DoNotInterrupt);
		StateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::Idle);
		return;
	}

	SelectorPoseSearchDatabase->SetInterruptMode(EPoseSearchInterruptMode::DoNotInterrupt);
	StateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::Walking);
}
