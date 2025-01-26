// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Interfaces/StaticMeshActorComponents/CurrentBallComponentInterface.h"
#include "CurrentBallComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEWPROJECT_API UCurrentBallComponent : public UActorComponent, public ICurrentBallComponentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCurrentBallComponent();

	virtual AActor* CurrentBall() override;
};
