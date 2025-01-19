#pragma once

#include "CoreMinimal.h"
#include "NewProject/Commons/Providers/Entities/EntityFactoryRegistry.h"
#include "NewProject/Entities/PoseSearchDatabases/PSD_DenseStandIdlesEntity.h"
#include "NewProject/Entities/PoseSearchDatabases/PSD_DenseStandRunLoopsEntity.h"
#include "NewProject/Entities/PoseSearchDatabases/PSD_DenseStandRunPivotsAllEntity.h"
#include "NewProject/Entities/PoseSearchDatabases/PSD_DenseStandWalkLoopsEntity.h"
#include "NewProject/Entities/PoseSearchDatabases/PSD_DenseStandWalkPivotsEntity.h"
#include "NewProject/Entities/PoseSearchDatabases/PSD_DenseStandWalkStartsEntity.h"
#include "NewProject/Entities/PoseSearchDatabases/PSD_DenseStandWalkStopsEntity.h"
#include "NewProject/Interfaces/Helpers/EntityAsset.h"


class NEWPROJECT_API FEntitiesAssetsLoadHelper final
{
public:
	FEntitiesAssetsLoadHelper()
	{
	}

	~FEntitiesAssetsLoadHelper()
	{
	}

	static void CreateEntitiesFromFiles(const FString& Directory, TArray<IEntityAsset*>& Entities)
	{
		// Encontrar os arquivos
		TArray<FString> FoundFiles;

		IFileManager& FileManager = IFileManager::Get();
		FileManager.FindFiles(FoundFiles, *Directory, TEXT("*.h"));

		if (FoundFiles.Num() > 0)
		{
			FoundFiles.RemoveAll([](const FString& FileName)
			{
				return FileName.IsEmpty(); // Remove arquivos com nomes vazios
			});
		}

		// Iterar pelos arquivos
		for (const FString& File : FoundFiles)
		{
			FString FileName = FPaths::GetBaseFilename(File);
			IEntityAsset* Entity = RegisterClass(TEXT("F") + FileName);
			if (!Entity)
			{
				UE_LOG(LogTemp, Warning, TEXT("Entity not valid"));
				continue;
			}
			Entities.Add(Entity);
		}
	}

	static IEntityAsset* RegisterClass(FString FileName)
	{
		// Mapeamento entre o nome do arquivo e a classe correspondente
		static TMap<FString, TFunction<IEntityAsset*()>> ClassMapping = {
			{
				TEXT("FPSD_DenseStandIdlesEntity"), []() -> IEntityAsset* {
					return new FPSD_DenseStandIdlesEntity();
				}
			},
			{
				TEXT("FPSD_DenseStandRunPivotsAllEntity"), []() -> IEntityAsset* {
					return new FPSD_DenseStandRunPivotsAllEntity();
				}
			},
			{
				TEXT("FPSD_DenseStandWalkPivotsEntity"), []() -> IEntityAsset* {
					return new FPSD_DenseStandWalkPivotsEntity();
				}
			},
			{
				TEXT("FPSD_DenseStandWalkStartsEntity"), []() -> IEntityAsset* {
					return new FPSD_DenseStandWalkStartsEntity();
				}
			},
			{
				TEXT("FPSD_DenseStandWalkStopsEntity"), []() -> IEntityAsset* {
					return new FPSD_DenseStandWalkStopsEntity();
				}
			},
			{
				TEXT("FPSD_DenseStandWalkLoopsEntity"), []() -> IEntityAsset* {
					return new FPSD_DenseStandWalkLoopsEntity();
				}
			},
			{
				TEXT("FPSD_DenseStandRunLoopsEntity"), []() -> IEntityAsset* {
					return new FPSD_DenseStandRunLoopsEntity();
				}
			},
		};

		if (ClassMapping.Contains(FileName))
		{
			// Obtém a fábrica definida no mapa e registra usando a função Register
			FEntityFactoryRegistry::Register(FileName, ClassMapping[FileName]);

			UE_LOG(LogTemp, Warning, TEXT("Classe registrada para FileName: %s"), *FileName);
			return FEntityFactoryRegistry::Create(FileName);
		}

		UE_LOG(LogTemp, Error, TEXT("Nenhuma classe encontrada para FileName: %s"), *FileName);
		return nullptr;
	}
};
