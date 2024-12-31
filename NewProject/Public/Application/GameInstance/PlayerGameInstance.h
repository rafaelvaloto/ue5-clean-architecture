// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlayerGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NEWPROJECT_API UPlayerGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override
	{
		Super::Init();

		UE_LOG(LogTemp, Warning, TEXT("PlayerGameInstance foi inicializado!"));
		// Lógica de inicialização global
	}
};
