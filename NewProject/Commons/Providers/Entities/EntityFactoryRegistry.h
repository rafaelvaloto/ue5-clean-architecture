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
class NEWPROJECT_API FEntityFactoryRegistry
{
public:
	virtual ~FEntityFactoryRegistry()
	{
		UE_LOG(LogTemp, Warning, TEXT("GetRegistry map: %d elements"), GetRegistry().Num());
		GetRegistry().Reset(); // Limpa o map
	}

	// Registro de classes
	static TMap<FString, FEntityFactoryFunction>& GetRegistry()
	{
		static TMap<FString, FEntityFactoryFunction> Registry;
		return Registry;
	}

	// Registrar uma fábrica no sistema
	static void Register(const FString& ClassName, FEntityFactoryFunction FactoryFunction)
	{
		GetRegistry().Add(ClassName, FactoryFunction);
	}

	// Criar uma entidade com base no nome da classe
	static IEntityAsset* Create(const FString& ClassName)
	{
		FString CorrectName = TEXT("F") + ClassName;
		FEntityFactoryFunction* FactoryFunction = GetRegistry().Find(CorrectName);
		if (!FactoryFunction || !*FactoryFunction)
		{
			UE_LOG(LogTemp, Warning, TEXT("Erro ao tentar criar classe ClassName:%s"), *CorrectName);
			return nullptr;
		}
		
		return (*FactoryFunction)();
	}
};
