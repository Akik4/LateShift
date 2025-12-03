// Fill out your copyright notice in the Description page of Project Settings.


#include "LateShiftInstance.h"

ULateShiftInstance::ULateShiftInstance() {
		looped = 0;
}

void ULateShiftInstance::AddLooped()
{
	looped++;
	UE_LOG(LogTemp, Warning, TEXT("Looping : %i"), looped);
}

void ULateShiftInstance::SetLooped(int num)
{
	looped = num;
}

void ULateShiftInstance::RemoveLooped()
{
	looped--;
	UE_LOG(LogTemp, Warning, TEXT("removed looping, actually : %i"), looped);
}

int ULateShiftInstance::GetLooped()
{
	return looped;
}

