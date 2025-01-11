// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>
#include "CoreMinimal.h"
#include "NewProject/Interfaces/Helpers/EntityAsset.h"

// Tipo de ponteiro para função de criação
typedef std::function<IEntityAsset*()> FEntityFactoryFunction;

/**
 * 
 */
struct NEWPROJECT_API FEntityFactoryRegistry final
{
private:
    // Registro de funções de fábrica (mapeamento de nomes de classes para funções fábricas)
    static TMap<FString, FEntityFactoryFunction>& GetRegistry()
    {
        static TMap<FString, FEntityFactoryFunction> Registry;
        return Registry;
    }

    // Mapa de instâncias já criadas (singleton por classe)
    static TMap<FString, IEntityAsset*>& GetInstanceCache()
    {
        static TMap<FString, IEntityAsset*> InstanceCache;
        return InstanceCache;
    }

public:
    // Registrar uma fábrica no sistema
    static void Register(const FString& ClassName, const FEntityFactoryFunction& FactoryFunction)
    {
        // Verifica se a classe já foi registrada
        if (GetRegistry().Contains(ClassName))
        {
            UE_LOG(LogTemp, Warning, TEXT("A classe %s já está registrada."), *ClassName);
            return;
        }

        // Registra a fábrica
        GetRegistry().Add(ClassName, FactoryFunction);

        // Cria e armazena a instância imediatamente após o registro
        IEntityAsset* NewInstance = FactoryFunction();
        if (NewInstance)
        {
            GetInstanceCache().Add(ClassName, NewInstance);
            UE_LOG(LogTemp, Warning, TEXT("Instância criada e armazenada para a classe: %s"), *ClassName);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Erro ao criar instância para a classe: %s"), *ClassName);
        }
    }

    // Criar uma entidade ou retornar uma instância já criada
    static IEntityAsset* Create(const FString& ClassName)
    {
        // Procura no cache de instâncias
        IEntityAsset** CachedInstance = GetInstanceCache().Find(ClassName);
        if (CachedInstance && *CachedInstance)
        {
            UE_LOG(LogTemp, Warning, TEXT("Retornando instância em cache para a classe: %s"), *ClassName);
            return *CachedInstance;
        }

        // Se a instância não existir, tenta criar novamente (fallback)
        FEntityFactoryFunction* FactoryFunction = GetRegistry().Find(ClassName);
        if (!FactoryFunction || !(*FactoryFunction))
        {
            UE_LOG(LogTemp, Warning, TEXT("Erro: Fábrica não encontrada para a classe: %s"), *ClassName);
            return nullptr;
        }

        IEntityAsset* NewInstance = (*FactoryFunction)();
        if (NewInstance)
        {
            GetInstanceCache().Add(ClassName, NewInstance);
            UE_LOG(LogTemp, Warning, TEXT("Nova instância criada e armazenada para a classe: %s"), *ClassName);
        }
        return NewInstance;
    }

    // Método para limpar o cache de instâncias
    static void ClearInstanceCache()
    {
        TMap<FString, IEntityAsset*>& InstanceCache = GetInstanceCache();

        // Iterar sobre o mapa e desalocar as instâncias criadas dinamicamente
        for (auto& Pair : InstanceCache)
        {
            if (Pair.Value)
            {
                // Deleta a instância
                delete Pair.Value;
                Pair.Value = nullptr; // Garante que o ponteiro não aponte para lixo
            }
        }

        // Limpa todas as entradas do cache
        InstanceCache.Empty();
        UE_LOG(LogTemp, Warning, TEXT("Todas as instâncias no cache foram desalocadas e o cache foi limpo."));
    }
};
