// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Commons/Providers/Entities/EntityFactoryRegistry.h"
#include "NewProject/Entities/PoseSearchDatabases/PSD_DenseStandIdlesEntity.h"
#include "NewProject/Entities/PoseSearchDatabases/PSD_SparseStandWalkStartsEntity.h"
#include "NewProject/Interfaces/Helpers/EntityAsset.h"
#include "EntitiesAssetsLoadHelper.generated.h"

/**
 * 
 */
UCLASS()
class NEWPROJECT_API UEntitiesAssetsLoadHelper : public UObject
{
	GENERATED_BODY()

public:
	UEntitiesAssetsLoadHelper()
	{
		RegisterEntities();
	}
	
	static void CreateEntitiesFromFiles(const FString& Directory, TArray<TSharedPtr<IEntityAsset>>& Entities)
	{
		// Encontrar os arquivos
		TArray<FString> FoundFiles;
		
		IFileManager& FileManager = IFileManager::Get();
		FileManager.FindFiles(FoundFiles, *Directory, TEXT("*.h"));

		if (FoundFiles.Num() > 0)
		{
			FoundFiles.RemoveAll([](const FString& FileName) {
				return FileName.IsEmpty(); // Remove arquivos com nomes vazios
			});	
		}

		// Iterar pelos arquivos
		for (const FString& File : FoundFiles)
		{
			FString FileName = FPaths::GetBaseFilename(File);
			UE_LOG(LogTemp, Warning, TEXT("Dir list FileName: %s"), *FileName);

			TSharedPtr<IEntityAsset> NewEntity = TSharedPtr<IEntityAsset>(FEntityFactoryRegistry::Create(FileName));
			if (!NewEntity)
			{
				UE_LOG(LogTemp, Warning, TEXT("Nenhuma classe encontrada para: %s"), *FileName);
				continue;
			}
			
			Entities.Add(NewEntity);
		}
	}

	static void RegisterEntities()
	{
		FEntityFactoryRegistry::Register(TEXT("FPSD_SparseStandWalkStartsEntity"), []() -> IEntityAsset* {
			return new FPSD_SparseStandWalkStartsEntity();
		});

		FEntityFactoryRegistry::Register(TEXT("FPSD_DenseStandIdlesEntity"), []() -> IEntityAsset* {
			return new FPSD_DenseStandIdlesEntity();
		});
		
		UE_LOG(LogTemp, Log, TEXT("Entities registradas com sucesso."));
	}
};
