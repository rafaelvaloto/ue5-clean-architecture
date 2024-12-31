#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPoseSearchDatabaseModeStateEnum : uint8
{
	Interrupted UMETA(DisplayName = "Interrupted"),
	NotInterrupted UMETA(DisplayName = "NotInterrupted"),
	InterruptedChangeDatabase UMETA(DisplayName = "InterruptedChangeDatabase"),
	InterruptedChangeDatabaseInvalid UMETA(DisplayName = "InterruptedChangeDatabaseInvalid")
};
