// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LateShiftInstance.generated.h"

/**
 * 
 */
UCLASS()
class LATESHIFT_API ULateShiftInstance : public UGameInstance
{
	GENERATED_BODY()
	ULateShiftInstance();

private:
	UPROPERTY()
	int looped;

public:
	void AddLooped();

	void SetLooped(int num);

	void RemoveLooped();

	int GetLooped();
	
};
