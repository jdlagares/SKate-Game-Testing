// Fill out your copyright notice in the Description page of Project Settings.


#include "N_ApplyImpulse.h"
#include "S_Character.h"
#include "S_SkateMovementComponent.h"

void UN_ApplyImpulse::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AS_Character* character = Cast<AS_Character>(MeshComp->GetOwner());
	if (character) {
		US_SkateMovementComponent* SkateMovementComp = Cast<US_SkateMovementComponent>(character->GetCharacterMovement());
		if (SkateMovementComp)
		{
			SkateMovementComp->AddAcelerationForce(AccelerationForce);
		}
	}
}
