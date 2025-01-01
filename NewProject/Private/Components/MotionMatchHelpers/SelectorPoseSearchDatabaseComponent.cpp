// Fill out your copyright notice in the Description page of Project Settings.


#include "NewProject/Public/Components/MotionMatchHelpers/SelectorPoseSearchDatabaseComponent.h"

#include "Components/Character/UpdateStateCharacterComponent.h"
#include "NewProject/Commons/Helpers/EntitiesAssetsLoadHelper.h"
#include "UseCases/SelectorPoseSearchDatabaseComponent/UpdateNodePoseSearchDatabaseUseCase.h"

// Sets default values for this component's properties
USelectorPoseSearchDatabaseComponent::USelectorPoseSearchDatabaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	UE_LOG(LogTemp, Log, TEXT("Object of USelectorPoseSearchDatabaseComponent created %p"), this);
}

USelectorPoseSearchDatabaseComponent::~USelectorPoseSearchDatabaseComponent()
{
	FoundHeaderFiles.Reset();
	FoundHeaderFiles.Empty();
	UE_LOG(LogTemp, Log, TEXT("Object of USelectorPoseSearchDatabaseComponent deleted %p"), this);	
}

void USelectorPoseSearchDatabaseComponent::BeginPlay()
{
	Super::BeginPlay();

	// Obtém uma referência ao componente UUpdateStateCharacterComponent no mesmo actor
	if (AActor* Owner = GetOwner())
	{
		UUpdateStateCharacterComponent* StateComponent = Owner->FindComponentByClass<UUpdateStateCharacterComponent>();
		if (StateComponent)
		{
			// Update Machine State Character, Idle, Walk etc..

			// Inscreve-se ao delegate para ouvir mudanças de estado
			StateComponent->OnStateChanged.AddDynamic(this, &USelectorPoseSearchDatabaseComponent::Handle);
		}
	}
}

TArray<TSharedPtr<IEntityAsset>> USelectorPoseSearchDatabaseComponent::GetEntitiesAsset()
{
	return FoundHeaderFiles;
}

void USelectorPoseSearchDatabaseComponent::Handle(EPlayerCharacterStateEnum CurrentState, EPlayerCharacterStateEnum PreviousState)
{
	UUpdateNodePoseSearchDatabaseUseCase::Handle(this, CurrentState, PreviousState);
}

AActor* USelectorPoseSearchDatabaseComponent::GetActor()
{
	return GetOwner();
}

void USelectorPoseSearchDatabaseComponent::LoadDatabaseAsset(const FString& DirectoryEntity)
{
	UE_LOG(LogTemp, Log, TEXT("Chamando funcao UEntitiesAssetsLoadHelper::CreateEntitiesFromFiles"));
	UEntitiesAssetsLoadHelper::CreateEntitiesFromFiles(DirectoryEntity, FoundHeaderFiles);

	if (FoundHeaderFiles.Num() > 0)
	{
		UE_LOG(LogTemp, Log, TEXT("FoundClass.Num() > 0, %d"), FoundHeaderFiles.Num());

		for (TSharedPtr<IEntityAsset> File : FoundHeaderFiles)
		{
			if (File.IsValid())
			{
				UPoseSearchDatabase* Asset = LoadObject<UPoseSearchDatabase>(nullptr, *File->GetPathAsset());
				if (Asset)
				{
					Databases.Add(Asset);
					UE_LOG(LogTemp, Log, TEXT("Add Databse: %s"), *File->GetPathAsset());
				}
				
				UE_LOG(LogTemp, Log, TEXT("PrintInformation: in FoundHeaderFiles"));
				File->PrintInformation();
			}
		}

		if (Databases.Num() > 0)
		{
			UE_LOG(LogTemp, Log, TEXT("Databses: %d"), Databases.Num());
		}
	}
}

void USelectorPoseSearchDatabaseComponent::DefaultDatabaseAsset(const FString& DirectoryEntityAsset)
{
	UPoseSearchDatabase* DefaultDB = LoadObject<UPoseSearchDatabase>(nullptr, *DirectoryEntityAsset);
	if (!DefaultDB)
	{
		UE_LOG(LogTemp, Warning, TEXT("DefaultDB not found"));
		return;
	}
	
	DatabaseCurrent = DefaultDB;
}

UPoseSearchDatabase* USelectorPoseSearchDatabaseComponent::GetDatabase()
{
	return DatabaseCurrent;
}

void USelectorPoseSearchDatabaseComponent::SetDatabaseCurrent(const uint32 Index)
{
	DatabaseCurrent = Databases[Index];
}
