// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewProject/Interfaces/Helpers/EntityAsset.h"
#include "NewProject/Interfaces/Helpers/RuleBase.h"

class NEWPROJECT_API FRuleManager: public IEntityAsset
{
	
public:
	FRuleManager() :
		NameAsset("DefaultRuleName"),
		PathAsset("DefaultRulePath")
	{
		UE_LOG(LogTemp, Warning, TEXT("Object of FRuleManager created at %p"), this);
	}
	
	//
	virtual ~FRuleManager() override
	{
		Rules.Reset();
		Rules.Empty();
		
		UE_LOG(LogTemp, Warning, TEXT("Object of FRuleManager deleted at %p"), this);
	}

	virtual ESelectorDatabaseValidateRuleModeEnum GetTypeValidateRule() override
	{
		return ESelectorDatabaseValidateRuleModeEnum::All;
	}

	/**
	 * Adiciona uma nova regra
	 */
	virtual void AddRule(const TSharedPtr<IRuleBase> Rule) override
	{
		Rules.Add(Rule);
	}

	virtual void ListRules() override
	{
		for (const TSharedPtr<IRuleBase> Rule : Rules)
		{
			UE_LOG(LogTemp, Log, TEXT("Listando Regras: %s"), *Rule->GetRuleName());
		}
	}

	/**
	 * Valida todas as regras em relação ao alvo fornecido
	 */
	virtual bool ValidateAll(const UObject* Target, const std::vector<std::any>& Params) override
	{
		if (!ValidWhen(Params))
		{
			UE_LOG(LogTemp, Warning, TEXT("ValidWhen falhou %s"), *GetNameAsset());
			return false;
		}

		UE_LOG(LogTemp, Warning, TEXT("ValidWhen passou %s"), *GetNameAsset());
		
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

	// Implementação do método abstrato por callback
	virtual bool ValidWhen(const std::vector<std::any>& Params) override
	{
		if (!Callback)
		{
			return true;
		}

		// Executa o callback com os parâmetros fornecidos
		return Callback(Params);
	}

	virtual FString GetNameAsset() override
	{
		return NameAsset;
	}

	virtual FString GetPathAsset() override
	{
		return PathAsset;
	}

	std::function<bool(const std::vector<std::any>&)> Callback;

protected:
	const char* NameAsset;
	const char* PathAsset;
	TArray<TSharedPtr<IRuleBase>> Rules;
};
