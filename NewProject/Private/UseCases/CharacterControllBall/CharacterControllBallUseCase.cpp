// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/CharacterControllBall/CharacterControllBallUseCase.h"
#include "Services/CurrentBall/CurrentBallService.h"

void UCharacterControllBallUseCase::Handle(
	const TScriptInterface<ISweepByChannelComponentInterface>& SweepByChannel,
	const TScriptInterface<ISelectClosestBoneCharacterComponentInterface>& SelectBoneComponent,
	const TScriptInterface<IUpdateStateCharacterComponentInterface>& StateCharacterComponent,
	const TScriptInterface<IPlayAnimMontageComponentInterface>& PlayAnimMontageComponent,
	const TScriptInterface<ISelectorPoseSearchDatabaseInterface>& SelectorPoseSearchDatabase
)
{
	if (
		SweepByChannel->DetectBallCollision() &&
		StateCharacterComponent->GetState() != EPlayerCharacterStateEnum::Controlling
	)
	{
		UE_LOG(LogTemp, Warning, TEXT("StateCharacterComponent->GetState() != EPlayerCharacterStateEnum::Controlling"));
		StateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::Controlling);
		SelectorPoseSearchDatabase->SetInterruptMode(EPoseSearchInterruptMode::ForceInterrupt);
		
		ESelectClosestBoneCharacterEnum DefineBoneAnim = SelectBoneComponent->SelectClosestFootBoneToBall(
			UCurrentBallService::CurrentBall());

		SelectBoneComponent->SetFoot(DefineBoneAnim);
		if (DefineBoneAnim == ESelectClosestBoneCharacterEnum::LeftFoot)
		{
			PlayAnimMontageComponent->PlayDynamicMontage(LoadObject<UAnimSequence>(
				nullptr, TEXT(
					"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/095_AA_Soccer_Player_DribbleF_L.095_AA_Soccer_Player_DribbleF_L"
				)), FName("DefaultSlot"), 0.8f, 0.0f,
															 0.0f, true);
			return;
		}

		PlayAnimMontageComponent->PlayDynamicMontage(LoadObject<UAnimSequence>(
			nullptr, TEXT(
				"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/094_AA_Soccer_Player_DribbleF_R.094_AA_Soccer_Player_DribbleF_R"
			)), FName("DefaultSlot"), 0.8f, 0.0f, 0.0f, true);
		return;
	}

	if (!SweepByChannel->DetectBallCollision() && StateCharacterComponent->GetState() == EPlayerCharacterStateEnum::Controlling)
	{
		PlayAnimMontageComponent->StopDynamicMontage();
		StateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::RunningPivot);
		SelectorPoseSearchDatabase->SetInterruptMode(EPoseSearchInterruptMode::DoNotInterrupt);
	}
}
