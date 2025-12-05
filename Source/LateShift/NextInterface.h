// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "NextInterface.generated.h"

/**
 * 
 */
UCLASS()
class LATESHIFT_API UNextInterface : public UUserWidget
{
	GENERATED_BODY()
	
public:
    // Bind to a widget created in the UserWidget Blueprint
    UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
    UTextBlock* LabelText;

    // Function to set text
    UFUNCTION(BlueprintCallable)
    void SetLabel(const FString& NewText);
};
