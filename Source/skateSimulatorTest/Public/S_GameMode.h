// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "S_GameMode.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int, newValue);

UCLASS()
class SKATESIMULATORTEST_API AS_GameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, Category = "Score")
	int MaxScore;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="Score")
	int CurrentScore;

	UPROPERTY(EditAnywhere, Category = "Score")
	TArray<class AS_Obscatule*> Obstacules;

	UPROPERTY(EditDefaultsOnly, Category = "Hud")
	TSubclassOf<UUserWidget> WinPanel;

protected:

	virtual void BeginPlay() override;

	void GameOver();

	UFUNCTION()
	void AddScore(int value);
	 
	UFUNCTION()
	void PlayerTriggerObstacule(AS_Obscatule* TriggeredObstacule);
public: 

	UPROPERTY(BlueprintAssignable)
	FOnScoreChanged OnScoreChanged;

};
