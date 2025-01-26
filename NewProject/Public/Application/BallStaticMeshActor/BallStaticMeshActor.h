// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshActor/CurrentBallComponent.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "BallStaticMeshActor.generated.h"

UCLASS()
class NEWPROJECT_API ABallStaticMeshActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABallStaticMeshActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Registrar os servicos
	void SetupServices() const;
	void SetupComponents();
	void SetupMesh() const;

	UFUNCTION()
	static void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, 
	                           const FHitResult& SweepResult);

	// Componente de Movimento de Projetil
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCurrentBallComponent* CurrentBallComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UFloatingPawnMovement* FloatingPawn;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsHandleComponent* PhysicsHandle;
};


