#include "PauseMenuWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyCharacter.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"

bool UPauseMenuWidget::Initialize()
{
    if (!Super::Initialize())
        return false;

    if (ResumeButton)
    {
        ResumeButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnResumeClicked);
    }
    if (ExitButton)
    {
        ExitButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnExitClicked);
    }

    return true;
}

void UPauseMenuWidget::OnResumeClicked()
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (!PC) return;

    AMyCharacter* MyChar = Cast<AMyCharacter>(PC->GetPawn());
    if (MyChar)
    {
        MyChar->TogglePause(FInputActionValue());
    }
}

void UPauseMenuWidget::OnExitClicked()
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        // Quits the game (works in editor and packaged builds)
        UGameplayStatics::OpenLevel(this, FName("main_menu"), true);
        /*UKismetSystemLibrary::QuitGame(
            GetWorld(),
            PC,
            EQuitPreference::Quit,
            true
        );*/
    }
}
