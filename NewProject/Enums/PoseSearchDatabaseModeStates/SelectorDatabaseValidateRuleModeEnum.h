#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ESelectorDatabaseValidateRuleModeEnum : uint8
{
	StateCharacter UMETA(DisplayName = "StateCharacter"),
	Velocity UMETA(DisplayName = "Velocity"),
	Deceleration UMETA(DisplayName = "Deceleration"),
	Acceleration UMETA(DisplayName = "Acceleration"),
	All UMETA(DisplayName = "All"),
};
