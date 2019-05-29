// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h" 
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	owner = GetOwner();

	if (!pressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing pressurePlate"), *GetOwner()->GetName())
	}
}

// Open the door to specified rotation
void UOpenDoor::OpenDoor()
{
	//Create a rotator; Set the door rotation
	owner->SetActorRotation(FRotator(0.0f, doorRotationAngle, 0.0f));
}

// Close the door to specified rotation
void UOpenDoor::CloseDoor()
{
	owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll the TriggerVolume
	if (GetTotalMassOfActorsOnPlate() > 30.0f)
	{
		OpenDoor();

		lastDoorOpenTime = GetWorld()->GetTimeSeconds(); // Returns time in seconds since the world was brought up for play
	}

	//If true, close the door
	if (GetWorld()->GetTimeSeconds() - lastDoorOpenTime > doorClosedelay)
	{
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float totalMass = 0.0f;

	TArray<AActor*> overlappingActors;

	if (!pressurePlate)
	{
		return totalMass;
	}
	//find all overlapping actors
	pressurePlate->GetOverlappingActors(OUT overlappingActors);

	//iterate through them, adding their masses
	for (const auto& actor : overlappingActors)
	{
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on pressurePlate"), *actor->GetName())
	}

	return totalMass;
}

