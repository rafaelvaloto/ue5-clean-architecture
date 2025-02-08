// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NewProject/Interfaces/StaticMeshActorComponents/CurrentBallComponentInterface.h"
#include "CurrentBallService.generated.h"

/**
 * 
 */
UCLASS()
class NEWPROJECT_API UCurrentBallService : public UObject
{
	GENERATED_BODY()

	// Referência estática para a instância global do serviço
	static ICurrentBallComponentInterface* BallServiceInstance;

public:
	static void RegisterService(ICurrentBallComponentInterface* Service);
	static bool IsServiceRegistered();

	static AActor* CurrentBall();
	static bool IsContact();

	
};
