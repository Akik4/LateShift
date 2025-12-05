// Fill out your copyright notice in the Description page of Project Settings.


#include "NextInterface.h"

void UNextInterface::SetLabel(const FString& NewText)
{
    if (LabelText)
    {
        LabelText->SetText(FText::FromString(NewText));
    }
}

void UNextInterface::SetSubLabel(const int text)
{
    FString val = "test";
    if (text == 0) val = "I just been hired. I should know this place";
    if (text == 1) val = "I feel like somethings is different";
    if (text > 1) val = "";

    if (SubLabelText) {
        SubLabelText->SetText(FText::FromString(val));
    }
}
