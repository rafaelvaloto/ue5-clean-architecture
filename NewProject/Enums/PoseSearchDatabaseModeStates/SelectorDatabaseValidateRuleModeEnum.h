#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ESelectorDatabaseValidateRuleModeEnum : uint8
{
	StateCharacter UMETA(DisplayName = "StateCharacter"),
	Velocity UMETA(DisplayName = "Velocity"),
	VelocityAndState UMETA(DisplayName = "VelocityAndState"),
	All UMETA(DisplayName = "All"),
};
