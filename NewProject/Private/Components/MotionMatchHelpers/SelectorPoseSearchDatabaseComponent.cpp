// Fill out your copyright notice in the Description page of Project Settings.


#include "NewProject/Public/Components/MotionMatchHelpers/SelectorPoseSearchDatabaseComponent.h"
#include "NewProject/Commons/Helpers/EntitiesAssetsLoadHelper.h"

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
				UE_LOG(LogTemp, Log, TEXT("Pin: %p in FoundHeaderFiles"), File.Get());
				UE_LOG(LogTemp, Log, TEXT("PrintInformation: in FoundHeaderFiles"));
				File->PrintInformation();
			}
		}
	}
}

UPoseSearchDatabase* USelectorPoseSearchDatabaseComponent::GetDatabase(const uint32 Index)
{
	return Databases[Index];
}
