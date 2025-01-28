// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Character/SweepByChannelComponent.h"
#include "Application/BallStaticMeshActor/BallStaticMeshActor.h"
#include "Application/PlayerCharacter/PlayerCharacter.h"


// Sets default values for this component's properties
USweepByChannelComponent::USweepByChannelComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USweepByChannelComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
}


// Called every frame
void USweepByChannelComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USweepByChannelComponent::DebugDrawLines(const bool IsDebug)
{
	bIsDebugDrawLines = IsDebug;
}

bool USweepByChannelComponent::DetectBallCollision()
{
	AActor* Actor = GetOwner();
	APlayerCharacter* Character = Cast<APlayerCharacter>(GetOwner());
	if (!Actor || !Character)
	{
		return false;
	}

	const float CapsuleRadius = 50.0f; // Raio da cápsula
	const float CapsuleHalfHeight = 100.0f; // Altura da cápsula (meia-altura)

	FRotator PlayerRotation = Character->GetActorRotation();
	FVector PlayerLocation = Character->GetActorLocation();

	// Cria a forma da cápsula
	FCollisionShape CapsuleShape = FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight);

	FCollisionQueryParams QueryParams(FName(TEXT("CapsuleSweep")), false, Actor);
	QueryParams.AddIgnoredActor(Actor); // Ignorar o próprio jogador

	// Configuração do QueryParams (detecção)
	const FVector Start = PlayerLocation; // Ponto inicial da cápsula
	const FVector End = Start + PlayerRotation.Vector() * CapsuleRadius;

	TArray<FHitResult> HitResults; // Vetor para armazenar todos os objetos atingidos no Sweep

	// Realiza o Capsule Sweep
	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults, // Resultado do Sweep
		Start, // Ponto inicial da cápsula
		End, // Ponto final (fixo, sem movimento)
		FQuat::Identity, // Orientação da cápsula
		ECC_Visibility, // Canal de detecção (ajustar conforme necessário)
		CapsuleShape, // Forma da cápsula
		QueryParams // Configurações de traçado
	);


	if (bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			// Verifica se o objeto atingido é a bola (`ABallStaticMeshActor`)
			ABallStaticMeshActor* Ball = Cast<ABallStaticMeshActor>(Hit.GetActor());
			if (Ball)
			{
				if (bIsDebugDrawLines)
				{
					DrawDebugCapsule(GetWorld(), Start, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, FColor::Red,
					                 false, 0.0f);
				}
				
				if (Character->UpdateStateCharacterComponent->GetState() == EPlayerCharacterStateEnum::Controlling)
				{
					// Calcula a nova posição da bola com base no pé do jogador
					FVector TargetLocation = PlayerLocation + (PlayerRotation.Vector() * 80.0f); // Ajuste de 50 unidades
					FVector SmoothedLocation = FMath::VInterpTo(Ball->GetActorLocation(), FVector(TargetLocation.X, TargetLocation.Y, Ball->GetActorLocation().Z), GetWorld()->GetDeltaSeconds(), 2.5f); // 10.0f é a rapidez da suavização
					Ball->SetActorLocation(SmoothedLocation);
				}
				
				// Ball->DisableComponentsSimulatePhysics();
				// Aplica a rotação
				return true;
			}

			if (bIsDebugDrawLines)
			{
				// Desenhar a cápsula no mundo para depuração (opcional)
				DrawDebugCapsule(GetWorld(), Start, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, FColor::Green,
				                 false, 0.0f);
			}
		}
	}

	if (Character->SelectorPoseSearchDatabaseComponent->GetInterruptMode() == EPoseSearchInterruptMode::ForceInterrupt)
	{
		Character->SelectorPoseSearchDatabaseComponent->SetInterruptMode(EPoseSearchInterruptMode::DoNotInterrupt);
	}
	
	Character->GetVelocity().Size() >= 20.f
		? Character->UpdateStateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::Running)
		: Character->UpdateStateCharacterComponent->SetCurrentState(EPlayerCharacterStateEnum::Walking);
	
	return false;
}

FHitResult USweepByChannelComponent::GetHitResult()
{
	return HitResult;
}
