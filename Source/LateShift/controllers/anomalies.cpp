// Fill out your copyright notice in the Description page of Project Settings.


#include "anomalies.h"

// Sets default values
Aanomalies::Aanomalies()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh->SetCollisionResponseToAllChannels(ECR_Block);
	Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	Mesh->SetGenerateOverlapEvents(true);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	BoxCollision->SetBoxExtent(FVector(50, 50, 50));
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Block);

	RootComponent = Mesh;
	BoxCollision->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void Aanomalies::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void Aanomalies::Init()
{
	AMyGameStateBase* e = GetWorld()->GetGameState<AMyGameStateBase>();
	ULateShiftInstance* GI = GetGameInstance<ULateShiftInstance>();
	if (GI->GetLooped() > 0)
	{
		isAppeared = (rand() % Aanomalies::rand_int) == 0;
	}
}

// Called every frame
void Aanomalies::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Aanomalies::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

