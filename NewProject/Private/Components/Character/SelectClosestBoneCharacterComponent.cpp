// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Character/SelectClosestBoneCharacterComponent.h"

#include "Application/PlayerCharacter/PlayerCharacter.h"

// Sets default values for this component's properties
USelectClosestBoneCharacterComponent::USelectClosestBoneCharacterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

ESelectClosestBoneCharacterEnum USelectClosestBoneCharacterComponent::SelectClosestFootBoneToBall(ABallStaticMeshActor* BallActor)
{
	const APlayerCharacter* Character = Cast<APlayerCharacter>(GetOwner());
	if (!Character)
	{
		UE_LOG(LogTemp, Error, TEXT("Character Actor or Mesh is null."));
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
	const FName ClosestBone = DistanceToLeftFoot < DistanceToRightFoot ? TEXT("foot_l") : TEXT("foot_r");
	UE_LOG(LogTemp, Warning, TEXT("Closest Foot Bone: %s"), *ClosestBone.ToString());

	if (ClosestBone == TEXT("foot_l"))
	{
		return ESelectClosestBoneCharacterEnum::LeftFoot;
	}
	
	return ESelectClosestBoneCharacterEnum::RightFoot;
}


// Called when the game starts
void USelectClosestBoneCharacterComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USelectClosestBoneCharacterComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

