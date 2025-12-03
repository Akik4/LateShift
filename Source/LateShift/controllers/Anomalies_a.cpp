// Fill out your copyright notice in the Description page of Project Settings.


#include "Anomalies_a.h"

AAnomalies_a::AAnomalies_a()
{
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