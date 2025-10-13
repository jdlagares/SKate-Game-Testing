// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "S_AmimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SKATESIMULATORTEST_API US_AmimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsInAir;

	class US_SkateMovementComponent* MovementComponent;


protected:

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSecods) override;
};
