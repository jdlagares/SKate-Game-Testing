// Fill out your copyright notice in the Description page of Project Settings.


#include "S_PlayerController.h"
#include "Blueprint/UserWidget.h"

void AS_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (WidgetClass) {
		UUserWidget* Widget = CreateWidget<UUserWidget>(this, WidgetClass);
		if (Widget) {
			Widget->AddToViewport();
		}

		bShowMouseCursor = false;
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
	}
}
