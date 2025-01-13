#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EWaitingNotifyAnimEnum : uint8
{
	None UMETA(DisplayName = "None"),
	Waiting UMETA(DisplayName = "Waiting"),
};
