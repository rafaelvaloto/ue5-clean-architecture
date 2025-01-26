// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Character/SelectClosestBoneCharacterComponent.h"
#include "GameFramework/Character.h"

USelectClosestBoneCharacterComponent::USelectClosestBoneCharacterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

ESelectClosestBoneCharacterEnum USelectClosestBoneCharacterComponent::SelectClosestFootBoneToBall(AActor* BallActor)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !BallActor)
	{
		UE_LOG(LogTemp, Error, TEXT("Character or BallActor is null, returning default value RightFoot."));
		return ESelectClosestBoneCharacterEnum::RightFoot;
	}

	// Obtenha as posições dos ossos no mundo
	const FVector LeftFootLocation = Character->GetMesh()->GetBoneLocation(TEXT("foot_l"), EBoneSpaces::WorldSpace);
	const FVector RightFootLocation = Character->GetMesh()->GetBoneLocation(TEXT("foot_r"), EBoneSpaces::WorldSpace);

	// Obtenha a posição do Ball Actor
	const FVector BallLocation = BallActor->GetActorLocation();

	// Calcular distâncias
	const float DistanceToLeftFoot = FVector::Dist(BallLocation, LeftFootLocation);
	const float DistanceToRightFoot = FVector::Dist(BallLocation, RightFootLocation);

	// Determine o osso mais próximo
	if (const FName ClosestBone = DistanceToLeftFoot < DistanceToRightFoot ? TEXT("foot_l") : TEXT("foot_r");
		ClosestBone == TEXT("foot_l"))
	{
		return ESelectClosestBoneCharacterEnum::LeftFoot;
	}

	return ESelectClosestBoneCharacterEnum::RightFoot;
}
