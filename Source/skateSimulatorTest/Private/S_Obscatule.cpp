// Fill out your copyright notice in the Description page of Project Settings.


#include "S_Obscatule.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "S_Character.h"
// Sets default values
AS_Obscatule::AS_Obscatule()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AS_Obscatule::BeginOverlapInteractZone);
	RootComponent = CollisionBox;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Obstacle"));
	Mesh->SetupAttachment(RootComponent);

	ArrowGuide = CreateDefaultSubobject<UArrowComponent>(TEXT("GUIDE"));
	ArrowGuide->SetupAttachment(RootComponent);

	SetObstacleState(EObstaculeState::EOS_NoCompleted);
}

// Called when the game starts or when spawned
void AS_Obscatule::BeginPlay()
{
	Super::BeginPlay();
	
}

void AS_Obscatule::BeginOverlapInteractZone(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AS_Character* Char = Cast<AS_Character>(OtherActor);
		if (Char) {
			SetObstacleState(EObstaculeState::EOS_Completed);
			OnPlayerTriggerObstacule.Broadcast(this);

		}
	}
}

void AS_Obscatule::SetObstacleState(EObstaculeState newState)
{
	ObstacleState = newState;
	switch (newState)
	{
		case EObstaculeState::EOS_Completed:
			CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			ArrowGuide->SetVisibility(false);
			break;
		case EObstaculeState::EOS_NoCompleted:
			CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
			ArrowGuide->SetVisibility(true);
			break;
	default:
		break;
	}
}


// Called every frame
void AS_Obscatule::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

