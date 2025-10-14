// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "S_Obscatule.generated.h"


UENUM(BlueprintType)
enum class EObstaculeState : uint8
{
	EOS_Completed				UMETA(DisplayName = "Completed"),
	EOS_NoCompleted			UMETA(DisplayName = "NoCompleted"),

	EOS_MAX			UMETA(DisplayName = "DefaultMAX")

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerTriggerObstacule, AS_Obscatule*,obstaculePassed);

UCLASS()
class SKATESIMULATORTEST_API AS_Obscatule : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AS_Obscatule();

	UPROPERTY(BlueprintAssignable)
	FOnPlayerTriggerObstacule OnPlayerTriggerObstacule;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction", meta=(AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* ArrowGuide;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	EObstaculeState ObstacleState;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void BeginOverlapInteractZone(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetObstacleState(EObstaculeState newState);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
