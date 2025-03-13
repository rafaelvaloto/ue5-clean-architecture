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

	const float CapsuleRadius = 60.0f; // Raio da cápsula
	const float CapsuleHalfHeight = 100.0f; // Altura da cápsula (meia-altura)

	FRotator PlayerRotation = Character->GetActorRotation();
	FVector PlayerLocation = Character->GetActorLocation();

	// Cria a forma da cápsula
	FCollisionShape CapsuleShape = FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Actor);
	QueryParams.AddIgnoredActor(Character);
	QueryParams.DefaultQueryParam.OwnerTag = TEXT("SweepByChannelComponent");
	QueryParams.DefaultQueryParam.bIgnoreBlocks = true;
	QueryParams.DefaultQueryParam.MobilityType = EQueryMobilityType::Dynamic;

	// Configuração do QueryParams (detecção)
	const FVector Start = PlayerLocation; // Ponto inicial da cápsula
	const FVector End = Start + (PlayerRotation.Vector() * CapsuleRadius); // + 

	TArray<FHitResult> HitResults; // Vetor para armazenar todos os objetos atingidos no Sweep

	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse = ECollisionResponse::ECR_Block;
	ResponseParams.DefaultResponseParam = ECollisionResponse::ECR_Block;

	// Realiza o Capsule Sweep
	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		Start,
		End,
		FQuat::Identity,
		ECC_Visibility,
		CapsuleShape,
		QueryParams
	);

	if (bIsDebugDrawLines)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Blue,
		              false, 0.0f);

		DrawDebugCapsule(GetWorld(), Start, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, FColor::Green,
		                 false, 0.0f);
	}

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

				if (
					Character->UpdateStateCharacterComponent->GetState() == EPlayerCharacterStateEnum::Controlling ||
					Character->UpdateStateCharacterComponent->GetState() == EPlayerCharacterStateEnum::ControllingTrajectoryChange
				)
				{
					ESelectClosestBoneCharacterEnum DefineBone = Character->ClosestBone->GetFoot();

					FVector FootBoneLocation = Character->GetMesh()->GetBoneLocation(
						TEXT("foot_l"), EBoneSpaces::WorldSpace);
					if (DefineBone == ESelectClosestBoneCharacterEnum::RightFoot)
					{
						FootBoneLocation = Character->GetMesh()->GetBoneLocation(
							TEXT("foot_r"), EBoneSpaces::WorldSpace);
					}

					FVector TargetLocation = FootBoneLocation + (PlayerRotation.Vector() * 200.f);
					FVector SmoothedLocation = FMath::VInterpTo(
						Ball->GetActorLocation(),
						FVector(TargetLocation.X, TargetLocation.Y, Ball->GetActorLocation().Z),
						GetWorld()->GetDeltaSeconds(),
						1.5f
					);

					if (bIsDebugDrawLines)
					{
						DrawDebugLine(GetWorld(), SmoothedLocation,
						              FVector(TargetLocation.X, TargetLocation.Y, Ball->GetActorLocation().Z),
						              FColor::Yellow,
						              false, 0.0f);
					}
				}
				return true;
			}
			
			if (!Hit.GetActor()->IsA(ABallStaticMeshActor::StaticClass()))
			{
				return false;	
			}
			return false;
		}
		return false;
	}
	return false;
}

FHitResult USweepByChannelComponent::GetHitResult()
{
	return HitResult;
}
