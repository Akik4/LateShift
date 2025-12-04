// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LateShift/controllers/anomalies.h"
#include "LateShift/Next.h"
#include "LateShift/LateShiftInstance.h"
#include "Kismet/GameplayStatics.h"
#include "LateShift/MyGameStateBase.h"
#include "LateShift/controllers/Anomalies_a.h"
#include "LateShift/controllers/Anomalies_d.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class LATESHIFT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void Mouse(const struct FInputActionValue& Value);
	void Move(const struct FInputActionValue& Value);
	void PlayFootstep();
	void RightClick(const struct FInputActionValue& Value);
	void Interact(const struct FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Audio")
	USoundBase* FootstepSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footsteps")
	float MovementSpeedThreshold = 10.f;

	FTimerHandle FootstepTimerHandle;
	bool bFootstepTimerActive = false;

	bool bIsMoving = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float FootstepInterval = 0.45f; // delay between steps when walking

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* CameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MouseAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MouseClick;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Interact;

	UPROPERTY(EditAnyWhere)
	double velocity;

	UPROPERTY(EditAnyWhere)
	double sensitivity;
	UPROPERTY(EditAnyWhere)
	int range;
};
