// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NewProject/Interfaces/CharacterComponents/PlayAnimMontageComponentInterface.h"
#include "PlayAnimMontageComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEWPROJECT_API UPlayAnimMontageComponent : public UActorComponent, public IPlayAnimMontageComponentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayAnimMontageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void PlayDynamicMontage(UAnimSequence* AnimationSequence, FName SlotName, float PlayRate) override;
	virtual void SetDynamicMontages(TArray<UAnimSequence*> AnimationSequences, FName SlotName, float PlayRate) override;
	virtual void DefineIndexPlayDynamicMontage(int32 Index) override;

private:
	UPROPERTY()
	int32 IndexPlayDynamicMontage = 0;

	UPROPERTY()
	TArray<UAnimSequence*> ArrayAnimationSequences;
};
