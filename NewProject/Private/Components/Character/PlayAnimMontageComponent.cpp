// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Character/PlayAnimMontageComponent.h"

#include "Application/PlayerCharacter/PlayerCharacter.h"


// Sets default values for this component's properties
UPlayAnimMontageComponent::UPlayAnimMontageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPlayAnimMontageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UPlayAnimMontageComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayAnimMontageComponent::StopDynamicMontage()
{
	const APlayerCharacter* Character = Cast<APlayerCharacter>(GetOwner());
	if (!Character->GetMesh() || !Character->GetMesh()->GetAnimInstance())
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Animation Sequence or Mesh/AnimInstance is null."));
		return;
	}

	
	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	AnimInstance->StopSlotAnimation(0.10, FName("DefaultSlot"));
}

void UPlayAnimMontageComponent::PlayDynamicMontage(UAnimSequence* AnimationSequence, FName SlotName, float PlayRate,
                                                   float NewPlayRate, float TimeToChangePlayRate, bool Loop)
{
	const APlayerCharacter* Character = Cast<APlayerCharacter>(GetOwner());
	if (!AnimationSequence || !Character->GetMesh() || !Character->GetMesh()->GetAnimInstance())
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Animation Sequence or Mesh/AnimInstance is null."));
		return;
	}

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

	if (
		AnimInstance->IsPlayingSlotAnimation(AnimationSequence, SlotName) ||
		AnimInstance->DynamicMontage_IsPlayingFrom(AnimationSequence)
	)
	{
		UE_LOG(LogTemp, Error, TEXT("Animation is already playing!"));
		return;
	}

	int32 LoopCount = 1;
	if (Loop)
	{
		UE_LOG(LogTemp, Error, TEXT("Entrou em loop!"));
		LoopCount = 100;
	}

	StopDynamicMontage();
	const UAnimMontage* DynamicMontage = AnimInstance->PlaySlotAnimationAsDynamicMontage(
		AnimationSequence, // A sequência de animação que será reproduzida
		SlotName, // Nome do slot no Animation Blueprint
		0.20f, // BlendInTime (tempo para interpolar o início da animação)
		0.10f, // BlendOutTime (tempo para interpolar o fim da animação)
		PlayRate, // PlayRate (taxa de reprodução da animação)
		LoopCount // LoopCount (número de vezes que a animação será executada)
	);
	
	if (DynamicMontage)
	{
		if (NewPlayRate > 0.0f && TimeToChangePlayRate > 0.0f)
		{
			// Ajustar automaticamente o PlayRate após o tempo desejado
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(
				TimerHandle,
				[AnimInstance, DynamicMontage, NewPlayRate]()
				{
					if (AnimInstance && DynamicMontage)
					{
						UE_LOG(LogTemp, Warning, TEXT("Dynamic Montage started change play rate!"));
						AnimInstance->Montage_SetPlayRate(DynamicMontage, NewPlayRate);
					}
				},
				TimeToChangePlayRate, // Tempo após o qual o PlayRate muda
				false // Não repete
			);
		}

		UE_LOG(LogTemp, Warning, TEXT("Dynamic Montage started successfully!"));
	}
}

void UPlayAnimMontageComponent::SetDynamicMontages(TArray<UAnimSequence*> AnimationSequences, const FName SlotName,
                                                   const float PlayRate, float NewPlayRate, float TimeToChangePlayRate,
                                                   bool Loop)
{
	if (ArrayAnimationSequences.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("ArrayAnimationSequences is not empty!"));
		ArrayAnimationSequences.Empty();
	}

	if (AnimationSequences.IsValidIndex(IndexPlayDynamicMontage))
	{
		ArrayAnimationSequences = AnimationSequences;
		PlayDynamicMontage(AnimationSequences[IndexPlayDynamicMontage], SlotName, PlayRate, NewPlayRate,
		                   TimeToChangePlayRate, Loop);
	}
}

void UPlayAnimMontageComponent::DefineIndexPlayDynamicMontage(const int32 Index, const FName SlotName,
                                                              const float PlayRate, bool Loop)
{
	if (!ArrayAnimationSequences.IsValidIndex(Index))
	{
		UE_LOG(LogTemp, Warning, TEXT("IsValidIndex is not valid!"));
		return;
	}
	PlayDynamicMontage(ArrayAnimationSequences[Index], SlotName, PlayRate, 0.0f, 0.0f);
}
