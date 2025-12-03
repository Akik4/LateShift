// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LateShift/MyGameStateBase.h"
#include "anomalies.h"
#include "Anomalies_a.generated.h"

/**
 * 
 */
UCLASS()
class LATESHIFT_API AAnomalies_a : public Aanomalies
{
	GENERATED_BODY()

public:
	AAnomalies_a();
	void Appear();

private:
	virtual void Init();

	
public:
	UPROPERTY(BlueprintReadOnly)
	bool bIsRevealed = false;

};
