// Fill out your copyright notice in the Description page of Project Settings.


#include "S_AmimInstance.h"
#include "S_SkateMovementComponent.h"

void US_AmimInstance::NativeInitializeAnimation()
{
	APawn* Pawn = TryGetPawnOwner();
	if (!Pawn) return;

	MovementComponent = Pawn->GetComponentByClass<US_SkateMovementComponent>();
}

void US_AmimInstance::NativeUpdateAnimation(float DeltaSecods)
{
	APawn* Pawn = TryGetPawnOwner();
	if (!Pawn) return;

	if (MovementComponent) {
		Speed = MovementComponent->Velocity.Size();
		bIsInAir = !MovementComponent->GetIsGrounded();
	}
}

