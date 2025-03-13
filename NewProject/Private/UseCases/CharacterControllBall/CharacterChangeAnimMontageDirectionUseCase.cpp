// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/CharacterControllBall/CharacterChangeAnimMontageDirectionUseCase.h"

#include "NewProject/Interfaces/CharacterComponents/UpdateAttributesCharacterComponentInterface.h"
#include "Services/CurrentBall/CurrentBallService.h"

void UCharacterChangeAnimMontageDirectionUseCase::Handle(
	const TScriptInterface<ISelectClosestBoneCharacterComponentInterface>& SelectBoneComponent,
	const TScriptInterface<IUpdateAttributesCharacterComponentInterface>& AttributesCharacter,
	const TScriptInterface<IUpdateStateCharacterComponentInterface>& StateCharacterComponent,
	const TScriptInterface<IPlayAnimMontageComponentInterface>& PlayAnimMontageComponent,
	const TScriptInterface<ISelectorPoseSearchDatabaseInterface>& SelectorPoseSearchDatabase,
	const FVector& Direction
)
{

	if (
		StateCharacterComponent->GetState() != EPlayerCharacterStateEnum::ControllingTrajectoryChange &&
		StateCharacterComponent->GetState() == EPlayerCharacterStateEnum::Controlling
	)
	{
		float PlayRate = 0.7f;
		
		const FVector ActorForwardVector =  AttributesCharacter->GetComponentActorForwardVector();
		const FVector NormalizedInputVector = Direction.GetSafeNormal();
		const FVector CrossProduct = FVector::CrossProduct(ActorForwardVector, NormalizedInputVector);

		StateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::ControllingTrajectoryChange);
		SelectorPoseSearchDatabase->SetInterruptMode(EPoseSearchInterruptMode::ForceInterrupt);
		const ESelectClosestBoneCharacterEnum Foot = SelectBoneComponent->GetFoot();
		if (
				CrossProduct.Z < 0.0f
			)
		{
			if (Foot == ESelectClosestBoneCharacterEnum::LeftFoot)
			{
				UAnimSequence* AnimSeq2 = LoadObject<UAnimSequence>(
					nullptr, TEXT(
						"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/098_AA_Soccer_Player_AdjustJog_CloseR01.098_AA_Soccer_Player_AdjustJog_CloseR01"
					));
	
				if (!AnimSeq2)
				{
					return;
				}
	
				PlayAnimMontageComponent->PlayDynamicMontage(
					AnimSeq2,
					FName("DefaultSlot"),
					PlayRate,
					0.0f,
					0.0f,
					false
				);
			}
			else
			{
				UAnimSequence* AnimSeq3 = LoadObject<UAnimSequence>(
					nullptr, TEXT(
						"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/099_AA_Soccer_Player_AdjustJog_CloseR02.099_AA_Soccer_Player_AdjustJog_CloseR02"
					));
	
				if (!AnimSeq3)
				{
					return;
				}
	
				PlayAnimMontageComponent->PlayDynamicMontage(
					AnimSeq3,
					FName("DefaultSlot"),
					PlayRate,
					0.0f,
					0.0f,
					false
				);
			}
		}
		else
		{
			if (Foot == ESelectClosestBoneCharacterEnum::LeftFoot)
			{
				UAnimSequence* AnimSeq = LoadObject<UAnimSequence>(
				nullptr, TEXT(
					"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/100_AA_Soccer_Player_AdjustJog_CloseL01.100_AA_Soccer_Player_AdjustJog_CloseL01"
				));
			
				if (!AnimSeq)
				{
					return;
				}
	
				PlayAnimMontageComponent->PlayDynamicMontage(
					AnimSeq,
					FName("DefaultSlot"),
					PlayRate,
					0.0f,
					0.0f,
					false
				);
			}
			else
			{
				UAnimSequence* AnimSeq1 = LoadObject<UAnimSequence>(
				nullptr, TEXT(
					"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/101_AA_Soccer_Player_AdjustJog_CloseL02.101_AA_Soccer_Player_AdjustJog_CloseL02"
				));
			
				if (!AnimSeq1)
				{
					return;
				}
	
				PlayAnimMontageComponent->PlayDynamicMontage(
					AnimSeq1,
					FName("DefaultSlot"),
					PlayRate,
					0.0f,
					0.0f,
					false
				);
			}
		}
	}
}
