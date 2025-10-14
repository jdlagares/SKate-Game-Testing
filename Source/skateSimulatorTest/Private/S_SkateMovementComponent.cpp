// Fill out your copyright notice in the Description page of Project Settings.


#include "S_SkateMovementComponent.h"
#include "EnhancedInputComponent.h"
US_SkateMovementComponent::US_SkateMovementComponent()
{
    GravityScale = 2.0f;
}

void US_SkateMovementComponent::PhysCustom(float DeltaTime, int32 Iterations)
{
	switch (CustomMovementMode)
	{
	case (uint8)ECustomMovementMode::MOVE_Skate:
		PhysSkate(DeltaTime, Iterations);
		break;
	default:
		Super::PhysCustom(DeltaTime, Iterations);
		break;
	}
}

void US_SkateMovementComponent::PhysSkate(float DeltaTime, int32 Iterations)
{
	if (!PawnOwner || !UpdatedComponent)
		return;

	// Detectar si está en el suelo
	CheckGrounded();

	FVector ImputDir = DirectionalVector.IsNearlyZero() ? PawnOwner->GetActorForwardVector() : DirectionalVector;

	if (bIsGrounded)
	{
		// Movimiento con fricción
		SkateVelocity += ImputDir * AccelerationForce * DeltaTime;
		SkateVelocity *= Friction;
	}
	else
	{
		// Movimiento en el aire con control limitado

		SkateVelocity += ImputDir * (AccelerationForce * AirControl) * DeltaTime;
		SkateVelocity.Z += GetGravityZ() * GravityScale * DeltaTime;
	}
	AccelerationForce = FMath::FInterpTo(AccelerationForce, 0.f, DeltaTime, 0.2f);
	// Limitar velocidad
	SkateVelocity.Z += GetGravityZ() * GravityScale * DeltaTime;
	
	if (SkateVelocity.Size() > MaxSpeed)
		SkateVelocity = SkateVelocity.GetSafeNormal() * MaxSpeed;

	FRotator NewRotation = PawnOwner->GetActorRotation();
	if (bOrientRotationToMovement && SkateVelocity.SizeSquared2D() > 1.f)
	{
		// Solo rota en plano (sin inclinar hacia arriba/abajo)
		FRotator TargetRotation = SkateVelocity.GetSafeNormal2D().Rotation();

		// Interpola suavemente hacia la nueva dirección
		 NewRotation = FMath::RInterpTo(
			PawnOwner->GetActorRotation(),
			TargetRotation,
			DeltaTime,
			8.f // velocidad de giro, ajústala al gusto
		);

	}
	// Movimiento del personaje
	FVector Delta = SkateVelocity * DeltaTime;
	FHitResult Hit;
	SafeMoveUpdatedComponent(Delta, NewRotation, true, Hit);

	if (Hit.IsValidBlockingHit())
	{
		SlideAlongSurface(Delta, 1.f - Hit.Time, Hit.Normal, Hit, true);
	}

	
	Velocity = SkateVelocity;
}

void US_SkateMovementComponent::CheckGrounded()
{
	FHitResult Hit;
	FVector Start = UpdatedComponent->GetComponentLocation();
	FVector End = Start - FVector(0, 0, lineDebugDistance); // Rayo corto hacia abajo

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(PawnOwner);
	if(bdebug)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2.0f);
	}
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

	if (bdebug) {
		DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 10.f, FColor::Yellow, false, 0.2f);
	}
	bIsGrounded = bHit && Hit.bBlockingHit && Hit.Normal.Z > 0.5f;

    if (bIsGrounded && SkateVelocity.Z < 0)
    {
        SkateVelocity.Z = 0;
        bIsJumping = false;
	}

}

void US_SkateMovementComponent::Jump()
{
	if (bIsGrounded)
	{
		bIsGrounded = false;
		bIsJumping = true;

		float ForwardBoost = FVector::DotProduct(SkateVelocity.GetSafeNormal2D(), PawnOwner->GetActorForwardVector());
		float AdjustedJumpForce = JumpForce * FMath::Lerp(1.f, 1.3f, ForwardBoost); // salto más alto si va rápido

		SkateVelocity.Z = AdjustedJumpForce;
	}
}

void US_SkateMovementComponent::AddAcelerationForce(float Value)
{
	AccelerationForce += Value;
	AccelerationForce = FMath::Max(AccelerationForce, 0.f);
}

