// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/CharacterControllBall/CharacterChangeDirectionControllBallUseCase.h"

#include "Services/CurrentBall/CurrentBallService.h"

void UCharacterChangeDirectionControllBallUseCase::Handle(
	const TScriptInterface<IUpdateAttributesCharacterComponentInterface>& UpdateAttributes,
	const TScriptInterface<IUpdateStateCharacterComponentInterface>& StateCharacterComponent
)
{
	if (
			StateCharacterComponent->GetState() == EPlayerCharacterStateEnum::Controlling &&
			UpdateAttributes->IsDetectedDirectionChange()
		)
	{
		FVector CurrentDirection = UpdateAttributes->GetVelocityCurrent().GetSafeNormal();
		FVector PrevDirection = UpdateAttributes->GetPreviousVelocity().GetSafeNormal();

		float DotProduct = FVector::DotProduct(PrevDirection, CurrentDirection);

		// Constrói o ângulo em graus
		float AngleInRadians = FMath::Acos(FMath::Clamp(DotProduct, -1.0f, 1.0f));
		float AngleInDegrees = FMath::RadiansToDegrees(AngleInRadians);

		// Verifica se a mudança de direção em Y é superior a 40 graus
		if (
				FMath::Abs(AngleInDegrees) > 45.f &&
				UCurrentBallService::IsContact()
			)
		{
			StateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::Interval);
			UE_LOG(LogTemp, Error, TEXT("AngleInDegrees: %f graus"), FMath::Abs(AngleInDegrees));
		}
	}
}
