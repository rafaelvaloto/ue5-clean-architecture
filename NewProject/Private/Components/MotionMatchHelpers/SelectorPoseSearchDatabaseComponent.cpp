// Fill out your copyright notice in the Description page of Project Settings.


#include "NewProject/Public/Components/MotionMatchHelpers/SelectorPoseSearchDatabaseComponent.h"

#include "NewProject/Commons/Helpers/EntitiesAssetsLoadHelper.h"
#include "Components/Character/UpdateAttributesCharacterComponent.h"
#include "Components/Character/UpdateStateCharacterComponent.h"
#include "UseCases/SelectorPoseSearchDatabaseComponent/UpdatePoseSearchDatabaseWithAccelerationUseCase.h"
#include "UseCases/SelectorPoseSearchDatabaseComponent/UpdatePoseSearchDatabaseWithStateUseCase.h"
#include "UseCases/SelectorPoseSearchDatabaseComponent/UpdatePoseSearchDatabaseWithDecelerationUseCase.h"

// Sets default values for this component's properties
USelectorPoseSearchDatabaseComponent::USelectorPoseSearchDatabaseComponent():
	bIsBlockingDeceleration(true),
	bIsBlockingAcceleration(true),
	WaitingNotifyAnim(EWaitingNotifyAnimEnum::None),
	DatabaseCurrent(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

USelectorPoseSearchDatabaseComponent::~USelectorPoseSearchDatabaseComponent()
{
	FEntityFactoryRegistry::ClearInstanceCache();
	UE_LOG(LogTemp, Warning, TEXT("USelectorPoseSearchDatabaseComponent::~USelectorPoseSearchDatabaseComponent"));
}

void USelectorPoseSearchDatabaseComponent::BeginPlay()
{
	Super::BeginPlay();

	if (DatabaseCurrent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("DatabaseCurrent not found"));
		return;
	}

	if (const AActor* Owner = GetOwner())
	{
		if (UUpdateStateCharacterComponent* StateComponent = Owner->FindComponentByClass<
			UUpdateStateCharacterComponent>())
		{
			StateComponent->OnStateChanged.AddDynamic(this, &USelectorPoseSearchDatabaseComponent::OnState);
		}

		UUpdateAttributesCharacterComponent* AttributesCharacterComponent = Owner->FindComponentByClass<
			UUpdateAttributesCharacterComponent>();
		if (AttributesCharacterComponent)
		{
			AttributesCharacterComponent->OnAcceleration.AddDynamic(
				this, &USelectorPoseSearchDatabaseComponent::OnAcceleration);
			AttributesCharacterComponent->OnDeceleration.AddDynamic(
				this, &USelectorPoseSearchDatabaseComponent::OnDeceleration);
		}
	}
}

TArray<IEntityAsset*> USelectorPoseSearchDatabaseComponent::GetEntitiesAsset()
{
	return FoundHeaderFiles;
}

void USelectorPoseSearchDatabaseComponent::OnState(const EPlayerCharacterStateEnum CurrentState,
                                                   const EPlayerCharacterStateEnum PreviousState)
{
	bIsBlockingDeceleration = true;
	bIsBlockingAcceleration = true;

	if (GetInterruptMode() == EPoseSearchInterruptMode::ForceInterrupt)
	{
		return;
	}

	if (
		const bool Return = UUpdatePoseSearchDatabaseWithStateUseCase::Handle(this, CurrentState, PreviousState); Return
	)
	{
		bIsBlockingDeceleration = false;
		bIsBlockingAcceleration = false;
	}
}

auto USelectorPoseSearchDatabaseComponent::OnDeceleration(const float PrevVelocity, float CurrentVelocity) -> void
{
	if (GetInterruptMode() == EPoseSearchInterruptMode::ForceInterrupt)
	{
		return;
	}

	if (bIsBlockingDeceleration)
	{
		return;
	}

	UUpdatePoseSearchDatabaseWithDecelerationUseCase::Handle(this, PrevVelocity, CurrentVelocity);
	bIsBlockingDeceleration = true;
}

void USelectorPoseSearchDatabaseComponent::OnAcceleration(const float PrevVelocity, const float CurrentVelocity,
                                                          const float Acceleration)
{
	if (GetInterruptMode() == EPoseSearchInterruptMode::ForceInterrupt)
	{
		return;
	}

	if (bIsBlockingAcceleration)
	{
		return;
	}

	UUpdatePoseSearchDatabaseWithAccelerationUseCase::Handle(this, PrevVelocity, CurrentVelocity, Acceleration);
	bIsBlockingAcceleration = true;
}

AActor* USelectorPoseSearchDatabaseComponent::GetActor()
{
	return GetOwner();
}

void USelectorPoseSearchDatabaseComponent::LoadDatabaseAsset(const FString& DirectoryEntity)
{
	FEntitiesAssetsLoadHelper::CreateEntitiesFromFiles(DirectoryEntity, FoundHeaderFiles);

	if (FoundHeaderFiles.Num() > 0)
	{
		for (IEntityAsset* File : FoundHeaderFiles)
		{
			if (UPoseSearchDatabase* Asset = LoadObject<UPoseSearchDatabase>(this, *File->GetPathAsset()))
			{
				Databases.Add(Asset);
			}
		}
	}
}

void USelectorPoseSearchDatabaseComponent::DefaultDatabaseAsset(const FString& DirectoryEntityAsset)
{
	UPoseSearchDatabase* DefaultDB = LoadObject<UPoseSearchDatabase>(this, *DirectoryEntityAsset);
	if (!DefaultDB)
	{
		UE_LOG(LogTemp, Error, TEXT("DefaultDB not found"));
		return;
	}

	DatabaseCurrent = DefaultDB;
}

void USelectorPoseSearchDatabaseComponent::SetInterruptMode(EPoseSearchInterruptMode Mode)
{
	InterruptModeCurrent = Mode;
}

EPoseSearchInterruptMode USelectorPoseSearchDatabaseComponent::GetInterruptMode()
{
	return InterruptModeCurrent;
}

void USelectorPoseSearchDatabaseComponent::SetWaitingNotifyAnim(EWaitingNotifyAnimEnum Mode)
{
	WaitingNotifyAnim = Mode;
}

EWaitingNotifyAnimEnum USelectorPoseSearchDatabaseComponent::GetWaitingNotifyAnim()
{
	return WaitingNotifyAnim;
}

UPoseSearchDatabase* USelectorPoseSearchDatabaseComponent::GetDatabase()
{
	return DatabaseCurrent;
}

void USelectorPoseSearchDatabaseComponent::SetDatabaseCurrent(const uint32 Index)
{
	DatabaseCurrent = Databases[Index];
}
