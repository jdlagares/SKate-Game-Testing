// Fill out your copyright notice in the Description page of Project Settings.

#include "S_Character.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "S_SkateMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

AS_Character::AS_Character(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<US_SkateMovementComponent>(TEXT("CharMoveComp")))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 180.0f; // the camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = true;//rotate the arm based on the controller

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);

	SkateboardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkateBoard"));
	SkateboardMesh->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void AS_Character::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->SetMovementMode(MOVE_Custom, (uint8)ECustomMovementMode::MOVE_Skate);
	
}

// Called every frame
void AS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AS_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	APlayerController* playerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());

	if (subsystem)
	{
		subsystem->ClearAllMappings();
		subsystem->AddMappingContext(InputMapping, 0);
	}

	UEnhancedInputComponent*  enhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (enhancedInputComp)
	{
		enhancedInputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AS_Character::Move);
		enhancedInputComp->BindAction(MoveAction, ETriggerEvent::Completed, this, &AS_Character::Move);
		enhancedInputComp->BindAction(LookAtAction, ETriggerEvent::Triggered, this, &AS_Character::LookAt);
		enhancedInputComp->BindAction(JumpAction, ETriggerEvent::Started, this, &AS_Character::Jump);
		enhancedInputComp->BindAction(ImpulseAction, ETriggerEvent::Triggered, this, &AS_Character::Impulse);
	}

}


void AS_Character::LookAt(const FInputActionValue& Value)
{
	if (Controller)
	{
		const FVector2D LookValue = Value.Get<FVector2D>();

		if (LookValue.X != 0.f)
		{
			AddControllerYawInput(LookValue.X);
		}

		if (LookValue.Y != 0.f)
		{
			AddControllerPitchInput(LookValue.Y);
		}
	}
}

void AS_Character::Move(const FInputActionValue& Value)
{
	const FVector MoveValue = Value.Get<FVector>();

	const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);

	const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	FVector Directional = (Forward * MoveValue.Y) + (Right * MoveValue.X);
	Directional = Directional.GetSafeNormal();

	US_SkateMovementComponent* SkateMovementComp = Cast<US_SkateMovementComponent>(GetCharacterMovement());
	SkateMovementComp->SetDirectional(Directional);
}

void AS_Character::Jump()
{
	US_SkateMovementComponent* SkateMovementComp = Cast<US_SkateMovementComponent>(GetCharacterMovement());
	if (SkateMovementComp)
	{
		SkateMovementComp->Jump();
	}
}

void AS_Character::Impulse()
{
	if (ImpulseMontage) {
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && !AnimInstance->Montage_IsPlaying(ImpulseMontage)) {
			US_SkateMovementComponent* SkateMovementComp = Cast<US_SkateMovementComponent>(GetCharacterMovement());
			if (SkateMovementComp) {
				if (SkateMovementComp->GetIsGrounded()) {
					AnimInstance->Montage_Play(ImpulseMontage, 1.0f);
				}
			}	
		}
	}
}

