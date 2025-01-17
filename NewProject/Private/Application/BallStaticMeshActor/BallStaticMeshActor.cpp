// Fill out your copyright notice in the Description page of Project Settings.


#include "Application/BallStaticMeshActor/BallStaticMeshActor.h"
#include "NewProject/Public/UseCases/SplineDrawComponent/TrajectoryRuntimeDrawUseCase.h"

// Sets default values
ABallStaticMeshActor::ABallStaticMeshActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spline = CreateDefaultSubobject<USplineDrawComponent>(TEXT("Spline"));
	Spline->RegisterComponent();
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BallStaticMesh(TEXT("/Script/Engine.StaticMesh'/Game/Soccer_set_1/Mesh/SM_soccer_ball_3.SM_soccer_ball_3'"));
	if (BallStaticMesh.Succeeded())
	{
		GetStaticMeshComponent()->SetStaticMesh(BallStaticMesh.Object);
		GetStaticMeshComponent()->SetMassOverrideInKg(NAME_None, 0.450f);
	}
	

	SetActorScale3D(FVector(1.1f, 1.1f, 1.1f));
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	GetStaticMeshComponent()->SetSimulatePhysics(false);
	GetStaticMeshComponent()->SetEnableGravity(true);
	GetStaticMeshComponent()->SetCollisionProfileName(TEXT("OverlapAll"));
	GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetStaticMeshComponent()->SetCollisionObjectType(ECC_PhysicsBody);  // Exemplo: Configurado para corpo físico
	GetStaticMeshComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	GetStaticMeshComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	//GetStaticMeshComponent()->SetCollisionResponseToAllChannels(ECR_Block);


	SetRootComponent(GetStaticMeshComponent());
	GetStaticMeshComponent()->SetupAttachment(RootComponent);
}

void ABallStaticMeshActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Colisão detectada com: %s"), *OtherActor->GetName());
}

// Called when the game starts or when spawned
void ABallStaticMeshActor::BeginPlay()
{
	GetStaticMeshComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABallStaticMeshActor::OnOverlapBegin);
	Super::BeginPlay();
}

// Called every frame
void ABallStaticMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// if (Spline)
	// {
	// 	FVector Trajectory = FVector(GetActorLocation().X * 2, GetActorLocation().Y * 2, 0.f);
	// 	UTrajectoryRuntimeDrawUseCase::Handle(Spline, Trajectory, DeltaTime);
	// }
}
