// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LateShift/LateShiftInstance.h"
#include "Components/BoxComponent.h"
#include "LateShift/MyGameStateBase.h"
#include "GameFramework/Pawn.h"
#include "anomalies.generated.h"

UCLASS()
class LATESHIFT_API Aanomalies : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	Aanomalies();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Init();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere)
	bool isAppeared;

	UPROPERTY(EditAnywhere)
	int rand_int;

};
