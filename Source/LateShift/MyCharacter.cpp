// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create camera
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(RootComponent);

    // Adjust camera position
    CameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 60.f));
    CameraComponent->bUsePawnControlRotation = true; // Makes camera rotate with mouse

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

void AMyCharacter::Interact(const FInputActionValue& value)
{
    FVector start = CameraComponent->GetComponentLocation();
    FVector end = start + CameraComponent->GetForwardVector() * 500;

    FHitResult HitResult;

    FCollisionQueryParams params;
    params.AddIgnoredActor(this);

    if (GetWorld()->LineTraceSingleByChannel(
        HitResult,
        start,
        end,
        ECC_EngineTraceChannel2,
        params
    )) {
        if (ANext* A = Cast<ANext>(HitResult.GetActor())) {
            AMyGameStateBase* e = GetWorld()->GetGameState<AMyGameStateBase>();
            ULateShiftInstance* GI = GetGameInstance<ULateShiftInstance>();
            if (e->GetAnomalie() == 0) {
                UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), true);
                GI->AddLooped();
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("WIN"));
            }
            else {
                UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), true);
                if (GI->GetLooped() > 1) {
                    GI->RemoveLooped();
                }
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("LOSE"));
            }
        }
    }

}

void AMyCharacter::RightClick(const FInputActionValue& Value) {
    ETraceTypeQuery channel = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel1);   
    TArray<FHitResult> hitResult = TArray<FHitResult>();

    FVector start = CameraComponent->GetComponentLocation() + CameraComponent->GetForwardVector() * 525;
    FVector end = start + CameraComponent->GetForwardVector() * range;
    UKismetSystemLibrary::SphereTraceMulti(
        GetWorld(),
        start,
        end,
        500,
        channel,
        true,
        {},
        EDrawDebugTrace::None,
        hitResult,
        true
        );

    AActor* actor;
    for (int i = 0; i < hitResult.Num(); i++) {
        actor = hitResult[i].GetActor();

        if (AAnomalies_a* A = Cast<AAnomalies_a>(actor)) {
            A->Appear();
            AMyGameStateBase* e = GetWorld()->GetGameState<AMyGameStateBase>();
            e->RemoveAnomalie();
        } 

        if (AAnomalies_d* D = Cast<AAnomalies_d>(actor)) {
            D->Destroy();
            AMyGameStateBase* e = GetWorld()->GetGameState<AMyGameStateBase>();
            e->RemoveAnomalie();
        }
        
    }
}

void AMyCharacter::TogglePause(const FInputActionValue& Value)
{
    APlayerController* PC = Cast<APlayerController>(GetController());
    if (!PC) return;

    bIsPaused = !bIsPaused; // toggle pause state

    if (bIsPaused)
    {
        if (!PauseMenuInstance && PauseMenuClass)
        {
            PauseMenuInstance = CreateWidget<UPauseMenuWidget>(PC, PauseMenuClass);
        }

        if (PauseMenuInstance && !PauseMenuInstance->IsInViewport())
        {
            PauseMenuInstance->AddToViewport();
        }

        PC->SetPause(true);
        PC->bShowMouseCursor = true;

        FInputModeUIOnly InputMode;
        InputMode.SetWidgetToFocus(PauseMenuInstance->TakeWidget());
        PC->SetInputMode(InputMode);
    }
    else
    {
        if (PauseMenuInstance && PauseMenuInstance->IsInViewport())
        {
            PauseMenuInstance->RemoveFromParent();
        }

        PC->SetPause(false);
        PC->bShowMouseCursor = false;

        FInputModeGameOnly InputMode;
        PC->SetInputMode(InputMode);
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
    EnhancedInput->BindAction(IA_Interact, ETriggerEvent::Started, this, &AMyCharacter::Interact);
    EnhancedInput->BindAction(IA_Pause, ETriggerEvent::Triggered, this, &AMyCharacter::TogglePause);
}


