#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPlayerCharacterStateEnum : uint8
{
	Idle UMETA(DisplayName = "Idle"), // Estado parado
	Dead UMETA(DisplayName = "Dead"), // Morto

	// States Locomotion
	Walking UMETA(DisplayName = "Walking"), // Andando
	WalkingPivot UMETA(DisplayName = "WalkingPivot"), // Andando
	Running UMETA(DisplayName = "Running"), // Correndo
	RunningPivot UMETA(DisplayName = "RunningPivot"), // Correndo

	// States Actions
	Controlling UMETA(DisplayName = "Controlling"), // Controlling
	Tackle UMETA(DisplayName = "Tackle"), // Boote
	TackleSlider UMETA(DisplayName = "TackleSlider"), // Carrinho

	Attacking UMETA(DisplayName = "Attacking"), // Atacando
	Jumping UMETA(DisplayName = "Jumping"), // Pulando
};
