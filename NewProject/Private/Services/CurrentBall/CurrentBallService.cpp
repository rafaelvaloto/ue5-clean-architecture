// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/CurrentBall/CurrentBallService.h"

ICurrentBallComponentInterface* UCurrentBallService::BallServiceInstance = nullptr;

void UCurrentBallService::RegisterService(ICurrentBallComponentInterface* Service)
{
	if (!Service)
	{
		UE_LOG(LogTemp, Log, TEXT("Attempted to register a null service to CurrentBallService."));
		return;
	}
	
	BallServiceInstance = Service;
}

bool UCurrentBallService::IsServiceRegistered()
{
	return BallServiceInstance != nullptr;
}

AActor* UCurrentBallService::CurrentBall()
{
	return BallServiceInstance->CurrentBall();
}
