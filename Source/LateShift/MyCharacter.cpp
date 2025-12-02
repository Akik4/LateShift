// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PC = Cast<APlayerController>(GetController());
    if (PC)
    {
        UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

        if (Subsystem)
        {
            Subsystem->AddMappingContext(InputMappingContext, 0);
        }
    }
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCharacter::Move(const FInputActionValue& Value)
{
    FVector2D Input = Value.Get<FVector2D>();

    AddMovementInput(GetActorForwardVector(), Input.Y * velocity);
    AddMovementInput(GetActorRightVector(), Input.X * velocity);
}

void AMyCharacter::Mouse(const FInputActionValue& Value)
{
    FVector2D Input = Value.Get<FVector2D>();

    AddControllerYawInput(Input.X * sensitivity);
    AddControllerPitchInput((Input.Y * -1)* sensitivity);
}


void AMyCharacter::RightClick(const FInputActionValue& Value) {
    ETraceTypeQuery channel = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel1);   
    TArray<FHitResult> hitResult = TArray<FHitResult>();
    FVector end = GetActorLocation() + UKismetMathLibrary::Multiply_VectorFloat(GetActorForwardVector(), 1000);
    UKismetSystemLibrary::SphereTraceMulti(
        GetWorld(),
        AMyCharacter::GetActorLocation(),
        end,
        500,
        channel,
        true,
        {},
        EDrawDebugTrace::ForDuration,
        hitResult,
        true
        );

    AActor* actor;
    for (int i = 0; i < hitResult.Num(); i++) {
        actor = hitResult[i].GetActor();
        actor->Destroy();
        AMyGameStateBase* e = GetWorld()->GetGameState<AMyGameStateBase>();
        e->RemoveAnomalie();
    }
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

    EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
    EnhancedInput->BindAction(MouseAction, ETriggerEvent::Triggered, this, &AMyCharacter::Mouse);
    EnhancedInput->BindAction(MouseClick, ETriggerEvent::Started, this, &AMyCharacter::RightClick);
}


