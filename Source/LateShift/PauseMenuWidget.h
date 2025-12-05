#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "PauseMenuWidget.generated.h"

UCLASS()
class LATESHIFT_API UPauseMenuWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;

    UPROPERTY(meta = (BindWidget))
    UButton* ResumeButton;

    UFUNCTION()
    void OnResumeClicked();

    UPROPERTY(meta = (BindWidget))
    UButton* ExitButton;

    UFUNCTION()
    void OnExitClicked();

};
