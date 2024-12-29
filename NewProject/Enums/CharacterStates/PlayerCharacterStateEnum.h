#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPlayerCharacterStateEnum : uint8
{
	Idle        UMETA(DisplayName = "Idle"),         // Estado parado
	Walking     UMETA(DisplayName = "Walking"),      // Andando
	Running     UMETA(DisplayName = "Running"),      // Correndo
	Jumping     UMETA(DisplayName = "Jumping"),      // Pulando
	Attacking   UMETA(DisplayName = "Attacking"),    // Atacando
	Dead        UMETA(DisplayName = "Dead")          // Morto
 };
