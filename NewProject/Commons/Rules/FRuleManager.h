// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Interfaces/Helpers/EntityAsset.h"
#include "NewProject/Interfaces/Helpers/RuleBase.h"

class NEWPROJECT_API FRuleManager: public IEntityAsset
{
	
public:
	virtual ~FRuleManager() override
	{
		UE_LOG(LogTemp, Warning, TEXT("Object of FRuleManager deleted at %p"), this);
		Rules.Empty();
		Rules.Reset();
	}
	
	TArray<TSharedPtr<IRuleBase>> Rules;

	/**
	 * Adiciona uma nova regra
	 */
	virtual void AddRule(const TSharedPtr<IRuleBase> Rule) override
	{
		Rules.Add(Rule);
	}

	/**
	 * Valida todas as regras em relação ao alvo fornecido
	 */
	virtual bool ValidateAll(const UObject* Target) override
	{
		for (const TSharedPtr<IRuleBase> Rule : Rules)
		{
			if (!Rule->Validate(Target))
			{
				UE_LOG(LogTemp, Warning, TEXT("Regra falhou: %s"), *Rule->GetRuleName());
				return false; // Falha na validação
			}
		}

		return true; // Todas as regras foram satisfeitas
	}

	/**
	 * Opcional: Lista todas as regras registradas
	 */
	virtual void ListRules() override
	{
		for (const TSharedPtr<IRuleBase>& Rule : Rules)
		{
			UE_LOG(LogTemp, Log, TEXT("Regra Registrada: %s"), *Rule->GetRuleName());
		}
	}

	// Implementação do método abstrato por callback
	virtual bool ValidWhen(const std::function<bool(const std::vector<std::any>&)>& Callback, const std::vector<std::any>& Params) override
	{
		if (!Callback)
		{
			return true; // Retorno padrão caso nenhum callback seja definido
		}

		// Executa o callback com os parâmetros fornecidos
		return Callback(Params);
	}

};
