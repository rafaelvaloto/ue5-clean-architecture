// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/InputCharacterComponent/ActionCharacterTackleUseCase.h"

#include "NewProject/Enums/PoseSearchDatabaseModeStates/WaitingNotifyAnimEnum.h"

void UActionCharacterTackleUseCase::Handle(
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
		StateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::Tackle);
		SelectorPoseSearchDatabase->SetInterruptMode(EPoseSearchInterruptMode::ForceInterrupt);

		UAnimSequence* MyAnimationSequence = LoadObject<UAnimSequence>(nullptr, TEXT("/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/077_AA_Soccer_Player_Tackle_L.077_AA_Soccer_Player_Tackle_L"));
		if (MyAnimationSequence)
		{
			Character->PlayDynamicMontage(MyAnimationSequence, FName("DefaultSlot"), 1.0f);
		}
		
		return;
	}

	if (StateCharacterComponent->GetState() != EPlayerCharacterStateEnum::Tackle)
	{
		return;
	}


	Character->StartInpulse = false;
	if (StateCharacterComponent->GetPeviousState() == EPlayerCharacterStateEnum::Tackle)
	{
		SelectorPoseSearchDatabase->SetWaitingNotifyAnim(EWaitingNotifyAnimEnum::None);
		StateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::Walking);
		return;
	}

	SelectorPoseSearchDatabase->SetWaitingNotifyAnim(EWaitingNotifyAnimEnum::None);
	StateCharacterComponent->SetCurrentState(StateCharacterComponent->GetPeviousState());
}
