// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"

void AMyGameStateBase::AddAnomalie()
{
	anomalies++;
	UE_LOG(LogTemp, Warning, TEXT("Added anomalie, actually : %i"), anomalies);
}

int AMyGameStateBase::GetAnomalie()
{
	return anomalies;
}
