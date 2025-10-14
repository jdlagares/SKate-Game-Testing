// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputActionValue.h"
#include "S_SkateMovementComponent.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ECustomMovementMode : uint8
{
    MOVE_Skate UMETA(DisplayName = "Skate")
};

UCLASS()
class SKATESIMULATORTEST_API US_SkateMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:

	US_SkateMovementComponent();
protected:

	float AccelerationForce = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skate Movement", meta = (AllowPrivateAccess = "true"))
    float DesaccelerationForce = 200.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skate Movement", meta = (AllowPrivateAccess = "true"))
    float MaxSpeed = 2000.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skate Movement", meta = (AllowPrivateAccess = "true"))
    float Friction = 0.98f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skate Jump", meta = (AllowPrivateAccess = "true"))
    float JumpForce = 600.0f;

    bool bIsJumping = false;
    bool bIsGrounded = false;

    FVector SkateVelocity;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
    FVector DirectionalVector;

    UPROPERTY(EditDefaultsOnly);
    float lineDebugDistance=100.0f

    UPROPERTY(EditDefaultsOnly);
    float ForwardDistance = 100.0f;
   
    FVector GroundNormal;



    UPROPERTY(EditDefaultsOnly);
    bool bdebug;
protected:

    virtual void PhysCustom(float DeltaTime, int32 Iterations) override;

    void PhysSkate(float DeltaTime, int32 Iterations);

    void CheckGrounded();

public:

     void Jump();

     void AddAcelerationForce(float Value);

     FORCEINLINE void SetDirectional(FVector newValue) { DirectionalVector = newValue; };
     FORCEINLINE FVector GetDirectional() { return DirectionalVector; };
     FORCEINLINE bool GetIsGrounded() { return bIsGrounded; };
   

};
