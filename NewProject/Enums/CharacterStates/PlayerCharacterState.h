#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EPlayerCharacterState
{
   Idle        UMETA(DisplayName = "Idle"),         // Estado parado
   Walking     UMETA(DisplayName = "Walking"),      // Andando
   Running     UMETA(DisplayName = "Running"),      // Correndo
   Jumping     UMETA(DisplayName = "Jumping"),      // Pulando
   Attacking   UMETA(DisplayName = "Attacking"),    // Atacando
   Dead        UMETA(DisplayName = "Dead")          // Morto
};
