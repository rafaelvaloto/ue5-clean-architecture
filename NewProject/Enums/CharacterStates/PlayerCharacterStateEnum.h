#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPlayerCharacterStateEnum : uint8
{
	Idle UMETA(DisplayName = "Idle"), // Estado parado
	
	Walking UMETA(DisplayName = "Walking"), // Andando
	WalkingPivot UMETA(DisplayName = "WalkingPivot"), // Andando
	Running UMETA(DisplayName = "Running"), // Correndo
	RunningPivot UMETA(DisplayName = "RunningPivot"), // Correndo
	Jumping UMETA(DisplayName = "Jumping"), // Pulando
	Attacking UMETA(DisplayName = "Attacking"), // Atacando
	Dead UMETA(DisplayName = "Dead"), // Morto
};
