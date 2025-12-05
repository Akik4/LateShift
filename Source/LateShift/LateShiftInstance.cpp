// Fill out your copyright notice in the Description page of Project Settings.


#include "LateShiftInstance.h"
#include "Kismet/GameplayStatics.h"

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

void ULateShiftInstance::ShowMainMenu()
{
    MainMenuInstance = CreateWidget<UUserWidget>(this, MainMenuClass);
    MainMenuInstance->AddToViewport();

    // Show mouse cursor
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        PC->bShowMouseCursor = true;
        PC->SetInputMode(FInputModeUIOnly());
    }
}

void ULateShiftInstance::StartGame()
{
    if (UWorld* World = GetWorld())
    {
        UGameplayStatics::OpenLevel(World, FName("default_map"));
    }
}

void ULateShiftInstance::QuitGame()
{
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}

