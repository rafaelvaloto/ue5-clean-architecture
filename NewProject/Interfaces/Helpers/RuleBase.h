// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

/**
 * 
 */
class NEWPROJECT_API IRuleBase
{
public:
	virtual ~IRuleBase()
	{
		IRuleBase* Rule = this;
		if (Rule != nullptr)
		{
			delete Rule;
			Rule = nullptr;
			UE_LOG(LogTemp, Warning, TEXT("IRuleBase destrutor chamado - %p"), Rule);
		}
	}

	/**
	 * Método para validar a regra
	 * 
	 * @param Target Elemento a ser avaliado contra a regra.
	 * @return Verdadeiro (true) se a regra foi satisfeita, falso (false) caso contrário.
	 */
	virtual bool Validate(const UObject* Target) const = 0;

	/**
	 * Opcional: Nome ou descrição da regra.
	 */
	virtual FString GetRuleName() const { return TEXT("Generic Rule"); }
};
