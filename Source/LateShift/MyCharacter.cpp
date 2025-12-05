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


    FlashLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("FlashLight"));
    FlashLight->SetupAttachment(CameraComponent);

    FlashLight->SetVisibility(false);          
    FlashLight->SetIntensity(3000); 
    FlashLight->AttenuationRadius = 3000.f;    
    FlashLight->bUseInverseSquaredFalloff = true;
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

    if (!NextInstance && NextInterfaceClass)
    {
        NextInstance = CreateWidget<UNextInterface>(PC, NextInterfaceClass);
    }

    if (NextInstance && !NextInstance->IsInViewport())
    {
        ULateShiftInstance* GI = GetGameInstance<ULateShiftInstance>();
        if (GI->GetLooped() == 7) {
            NextInstance->SetLabel("You win");
            NextInstance->AddToViewport();
        }
        else {
            NextInstance->SetLabel(FString::FromInt(GI->GetLooped()));
            NextInstance->SetSubLabel(GI->GetLooped());
            NextInstance->AddToViewport();

            GetWorld()->GetTimerManager().SetTimer(
                DelayHandle,
                this,
                &AMyCharacter::MyDelayedFunction,
                5.f,    // delay in seconds
                false    // no loop
            );
        }
    }
}

void AMyCharacter::MyDelayedFunction()
{
    NextInstance->RemoveFromParent();
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    ShowInterface();

    FVector Vel = GetVelocity();
    float SpeedSq = Vel.SizeSquared();

    bIsMoving = SpeedSq > FMath::Square(MovementSpeedThreshold);


    if (bIsMoving && !bFootstepTimerActive)
    {
        float Interval = FootstepInterval;

        GetWorldTimerManager().SetTimer(
            FootstepTimerHandle,
            this,
            &AMyCharacter::PlayFootstep,
            Interval,
            true,
            0.f
        );

        bFootstepTimerActive = true;
    }
    else if ((!bIsMoving) && bFootstepTimerActive)
    {
        GetWorldTimerManager().ClearTimer(FootstepTimerHandle);
        bFootstepTimerActive = false;
    }

}

void AMyCharacter::Move(const FInputActionValue& Value)
{
    if (bIsPaused) return;
    FVector2D Input = Value.Get<FVector2D>();

    AddMovementInput(GetActorForwardVector(), Input.Y * velocity);
    AddMovementInput(GetActorRightVector(), Input.X * velocity);
}

void AMyCharacter::PlayFootstep()
{
    UGameplayStatics::PlaySoundAtLocation(
        this,
        FootstepSound,
        GetActorLocation()
    );
}

void AMyCharacter::PlayPhoto()
{
    UGameplayStatics::PlaySoundAtLocation(
        this,
        PhotoSound,
        GetActorLocation()
    );
}

void AMyCharacter::Mouse(const FInputActionValue& Value)
{
    if (bIsPaused) return;
    FVector2D Input = Value.Get<FVector2D>();

    AddControllerYawInput(Input.X * sensitivity);
    AddControllerPitchInput((Input.Y * -1)* sensitivity);
}

void AMyCharacter::ShowInterface()
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
        AActor* HitActor = HitResult.GetActor();
        if (UWidgetComponent* Widget = HitActor->FindComponentByClass<UWidgetComponent>())
        {
            Widget->SetVisibility(true);
        } 
    } else {
        HideAllInteractionWidgets();
    }
}

void AMyCharacter::HideAllInteractionWidgets()
{
    for (TActorIterator<AActor> It(GetWorld()); It; ++It)
    {
        if (UWidgetComponent* Widget = It->FindComponentByClass<UWidgetComponent>())
        {
            Widget->SetVisibility(false);
        }
    }
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
                    GI->SetLooped(1);
                }
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("LOSE"));
            }
        }
    }

}

void AMyCharacter::RightClick(const FInputActionValue& Value) {

    if (!bCanRightClick)
    {
        return;
    }

    bCanRightClick = false;
    GetWorldTimerManager().SetTimer(
        RightClickCooldownHandle,
        this,
        &AMyCharacter::ResetRightClickCooldown,
        RightClickCooldown,
        false
    );

    PlayPhoto();
    StartCameraFlashSequence();

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
        EDrawDebugTrace::ForDuration,
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
void AMyCharacter::ResetRightClickCooldown()
{
    bCanRightClick = true;
}
void AMyCharacter::StartCameraFlashSequence()
{
    if (!FlashLight || TotalFlashes <= 0)
        return;

    GetWorldTimerManager().ClearTimer(FlashTimerHandle);
    CurrentFlashIndex = 0;
    bFlashIsOn = false;

    HandleFlashStep();
}

void AMyCharacter::HandleFlashStep()
{
    if (!FlashLight)
        return;

    if (!bFlashIsOn)
    {
        float IntensityToUse = FlashIntensity;
        if (CurrentFlashIndex == 0) // pré-flash
        {
            IntensityToUse = FlashIntensity * PreFlashIntensityFactor;
        }

        FlashLight->SetIntensity(IntensityToUse);
        FlashLight->SetVisibility(true);
        bFlashIsOn = true;

        GetWorldTimerManager().SetTimer(
            FlashTimerHandle,
            this,
            &AMyCharacter::HandleFlashStep,
            FlashOnTime,
            false
        );
    }
    else
    {
        FlashLight->SetVisibility(false);
        bFlashIsOn = false;
        CurrentFlashIndex++;

        if (CurrentFlashIndex >= TotalFlashes)
        {
            GetWorldTimerManager().ClearTimer(FlashTimerHandle);
            return;
        }

        GetWorldTimerManager().SetTimer(
            FlashTimerHandle,
            this,
            &AMyCharacter::HandleFlashStep,
            FlashOffTime,
            false
        );
    }
}


void AMyCharacter::TogglePause(const FInputActionValue& Value)
{
    APlayerController* PC = Cast<APlayerController>(GetController());
    if (!PC) return;

    bIsPaused = !bIsPaused;

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

        FInputModeGameAndUI InputMode;
        InputMode.SetWidgetToFocus(PauseMenuInstance->TakeWidget());
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        PC->SetInputMode(InputMode);

        PC->bShowMouseCursor = true;
        PC->SetPause(true);

    }
    else
    {
        if (PauseMenuInstance && PauseMenuInstance->IsInViewport())
        {
            PauseMenuInstance->RemoveFromParent();
        }

        FInputModeGameOnly InputMode;
        PC->SetInputMode(InputMode);

        PC->bShowMouseCursor = false;
        PC->SetPause(false);
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
    EnhancedInput->BindAction(IA_Pause, ETriggerEvent::Started, this, &AMyCharacter::TogglePause);
}


