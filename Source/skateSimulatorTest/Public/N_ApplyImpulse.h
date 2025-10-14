// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "N_ApplyImpulse.generated.h"

/**
 * 
 */
UCLASS()
class SKATESIMULATORTEST_API UN_ApplyImpulse : public UAnimNotify
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere)
	float AccelerationForce= 1000.0f;

protected:

	virtual void Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation) override;
};
