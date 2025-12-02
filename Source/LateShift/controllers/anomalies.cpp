// Fill out your copyright notice in the Description page of Project Settings.


#include "anomalies.h"

// Sets default values
Aanomalies::Aanomalies()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void Aanomalies::BeginPlay()
{
	Super::BeginPlay();

	isAppeared = 0 + (rand() % (1 - 0 + 1)) == 1;



	if (!isAppeared) {
		Destroy();
	}
	else {
		if (GetWorld() != NULL) {
			AMyGameStateBase* e = GetWorld()->GetGameState<AMyGameStateBase>();
			e->AddAnomalie();
		}
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

