// Fill out your copyright notice in the Description page of Project Settings.


#include "NextInterface.h"

void UNextInterface::SetLabel(const FString& NewText)
{
    if (LabelText)
    {
        LabelText->SetText(FText::FromString(NewText));
    }
}
