// Fill out your copyright notice in the Description page of Project Settings.


#include "Anomalies_a.h"

AAnomalies_a::AAnomalies_a()
{
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


	bIsRevealed = true;
}

void AAnomalies_a::Init()
{
	Super::Init();

	BoxCollision->SetCollisionResponseToChannel(ECC_EngineTraceChannel2, ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
	Mesh->SetVisibility(true);
	if (isAppeared) {
		BoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		BoxCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
		Mesh->SetVisibility(false);
		bIsRevealed = false;
		AMyGameStateBase* e = GetWorld()->GetGameState<AMyGameStateBase>();
		e->AddAnomalie();
	}
}

void AAnomalies_a::Appear()
{
	Mesh->SetVisibility(true);
	BoxCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	bIsRevealed = true;
}