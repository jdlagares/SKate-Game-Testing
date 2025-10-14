// Fill out your copyright notice in the Description page of Project Settings.


#include "S_GameMode.h"
#include "S_Character.h"
#include "S_Obscatule.h"
#include "Kismet/GameplayStatics.h" 
#include "Blueprint/UserWidget.h"

void AS_GameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors; // Declare an array to store the found actors
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AS_Obscatule::StaticClass(), FoundActors);
	for (AActor* actor: FoundActors){
		Obstacules.Add(Cast<AS_Obscatule>(actor));
	}
	for (AS_Obscatule* obstacule: Obstacules)
	{
		obstacule->OnPlayerTriggerObstacule.AddUniqueDynamic(this, &AS_GameMode::PlayerTriggerObstacule);
	}
	MaxScore = Obstacules.Num();
	AddScore(0);
}

void AS_GameMode::GameOver()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC) return;

	// Game OverState
	PC->bShowMouseCursor = true;


	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetWidgetToFocus(nullptr); 
	PC->SetInputMode(InputMode);

	UGameplayStatics::SetGamePaused(this, true);

	if (WinPanel )
	{
		UUserWidget* GameOverWidget = CreateWidget<UUserWidget>(PC, WinPanel);
		if (GameOverWidget)
		{
			GameOverWidget->AddToViewport();
		}
	}
}

void AS_GameMode::AddScore(int value)
{
	CurrentScore += value;
	OnScoreChanged.Broadcast(CurrentScore);
	if (CurrentScore == MaxScore) {
		GameOver();
	}
}

void AS_GameMode::PlayerTriggerObstacule(AS_Obscatule* TriggeredObstacule)
{
	AddScore(1);
}
