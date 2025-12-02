// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../MyGameStateBase.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShiftGameBase.generated.h"

/**
 * 
 */
UCLASS()
class LATESHIFT_API AShiftGameBase : public AGameModeBase
{
	GENERATED_BODY()

public: 

	AShiftGameBase();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	
};
