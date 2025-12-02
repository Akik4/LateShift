// Fill out your copyright notice in the Description page of Project Settings.


#include "ShiftGameBase.h"

AShiftGameBase::AShiftGameBase()
{
	GameStateClass = AMyGameStateBase::StaticClass();
}

void AShiftGameBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) {
	Super::InitGame(MapName, Options, ErrorMessage);
	UE_LOG(LogTemp, Warning, TEXT("Loaded"))
}
