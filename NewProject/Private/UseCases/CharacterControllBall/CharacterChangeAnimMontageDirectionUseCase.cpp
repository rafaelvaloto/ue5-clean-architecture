// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/CharacterControllBall/CharacterChangeAnimMontageDirectionUseCase.h"
#include "Services/CurrentBall/CurrentBallService.h"

void UCharacterChangeAnimMontageDirectionUseCase::Handle(
	const TScriptInterface<ISelectClosestBoneCharacterComponentInterface>& SelectBoneComponent,
	const TScriptInterface<IUpdateStateCharacterComponentInterface>& StateCharacterComponent,
	const TScriptInterface<IPlayAnimMontageComponentInterface>& PlayAnimMontageComponent,
	const TScriptInterface<ISelectorPoseSearchDatabaseInterface>& SelectorPoseSearchDatabase,
	const FVector& Direction
)
{
	if (
		StateCharacterComponent->GetState() != EPlayerCharacterStateEnum::ControllingTrajectoryChange &&
		StateCharacterComponent->GetState() != EPlayerCharacterStateEnum::Controlling
	)
	{
		float PlayRate = 0.7f;

		StateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::ControllingTrajectoryChange);
		SelectorPoseSearchDatabase->SetInterruptMode(EPoseSearchInterruptMode::ForceInterrupt);

		ESelectClosestBoneCharacterEnum Bone = SelectBoneComponent->GetFoot();
		if (Bone == ESelectClosestBoneCharacterEnum::LeftFoot)
		{
			if (Direction.Y < 0.0f)
			{
				UE_LOG(LogTemp, Error, TEXT("Direction.Y < 0.0f Bone: %d, LeftFoot"), (int)Bone);
				UAnimSequence* AnimSeq = LoadObject<UAnimSequence>(
					nullptr, TEXT(
						"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/099_AA_Soccer_Player_AdjustJog_CloseR02.099_AA_Soccer_Player_AdjustJog_CloseR02"
					));

				if (!AnimSeq)
				{
					UE_LOG(LogTemp, Error, TEXT("AnimSeq not found"));
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
				return;
			}

			UAnimSequence* AnimSeq = LoadObject<UAnimSequence>(
				nullptr, TEXT(
					"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/100_AA_Soccer_Player_AdjustJog_CloseL01.100_AA_Soccer_Player_AdjustJog_CloseL01"
				));

			if (!AnimSeq)
			{
				UE_LOG(LogTemp, Error, TEXT("AnimSeq not found"));
				return;
			}

			UE_LOG(LogTemp, Error, TEXT("Direction.Y > 0.0f Bone: %d, LeftFoot"), (int)Bone);
			PlayAnimMontageComponent->PlayDynamicMontage(
				AnimSeq,
				FName("DefaultSlot"),
				PlayRate,
				0.0f,
				0.0f,
				false
			);
			return;
		}


		if (Direction.Y < 0.0f)
		{
			UAnimSequence* AnimSeq = LoadObject<UAnimSequence>(
				nullptr, TEXT(
					"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/103_AA_Soccer_Player_AdjustJog_FarR02.103_AA_Soccer_Player_AdjustJog_FarR02"
				));

			if (!AnimSeq)
			{
				UE_LOG(LogTemp, Error, TEXT("AnimSeq not found"));
				return;
			}
			
			UE_LOG(LogTemp, Error, TEXT("Direction.Y < 0.0f Bone: %d, RightFoot"), (int)Bone);
			PlayAnimMontageComponent->PlayDynamicMontage(
				AnimSeq,
				FName("DefaultSlot"),
				PlayRate,
				0.0f,
				0.0f,
				false
			);

			return;
		}

		UAnimSequence* AnimSeq = LoadObject<UAnimSequence>(
			nullptr, TEXT(
				"/Game/Characters/UEFN_Mannequin/Animations/Roboot_A1/102_AA_Soccer_Player_AdjustJog_FarR01.102_AA_Soccer_Player_AdjustJog_FarR01"
			));

		if (!AnimSeq)
		{
			UE_LOG(LogTemp, Error, TEXT("AnimSeq not found"));
			return;
		}

		UE_LOG(LogTemp, Error, TEXT("Direction.Y > 0.0f Bone: %d, RightFoot"), (int)Bone);
		PlayAnimMontageComponent->PlayDynamicMontage(
			AnimSeq,
			FName("DefaultSlot"),
			PlayRate,
			0.0f,
			0.0f,
			false
		);
	}
}
