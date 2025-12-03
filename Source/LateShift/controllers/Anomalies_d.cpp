// Fill out your copyright notice in the Description page of Project Settings.


#include "Anomalies_d.h"

void AAnomalies_d::Init()
{
	Super::Init();

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
