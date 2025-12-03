// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LateShift/MyGameStateBase.h"
#include "anomalies.h"
#include "Anomalies_d.generated.h"

/**
 * 
 */
UCLASS()
class LATESHIFT_API AAnomalies_d : public Aanomalies
{
	GENERATED_BODY()

private:
		virtual void Init() override;
	
};
