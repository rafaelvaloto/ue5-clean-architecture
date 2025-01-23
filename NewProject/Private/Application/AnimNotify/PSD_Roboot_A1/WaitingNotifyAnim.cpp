// Fill out your copyright notice in the Description page of Project Settings.

#include "Application/AnimNotify/PSD_Roboot_A1/WaitingNotifyAnim.h"
#include "Application/PlayerCharacter/PlayerCharacter.h"
#include "UseCases/InputCharacterComponent/ActionCharacterTackleUseCase.h"

// Lógica executada ao final da animação.
void UWaitingNotifyAnim::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	// Garante que o MeshComp é válido.
	if (!MeshComp) return;
	
	APlayerCharacter* Character = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (!Character) return;

	Character->StartInpulse = false;
	Character->SelectorPoseSearchDatabaseComponent->SetInterruptMode(EPoseSearchInterruptMode::DoNotInterrupt);
	
	float Velocity = Character->GetVelocity().Size();
	if (Velocity > 0.1 && Velocity < 10.0f)
	{
		Character->UpdateStateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::Walking);
		return;
	}

	if (Velocity > 15.0f)
	{
		Character->UpdateStateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::Running);
		return;
	}
	
	if (Velocity < 0.01f)
	{
		Character->UpdateStateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::Idle);
	}
}
