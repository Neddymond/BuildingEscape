// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h" 
#include "GameFramework/PlayerController.h"


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

	//Get the default pawn 
	actorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	//Find the owning Actor
	AActor* owner = GetOwner();

	//Create a rotator
	FRotator newRotation = FRotator(0.0f, doorRotationAngle, 0.0f);

	//Set the door rotation
	owner->SetActorRotation(newRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll the TriggerVolume; If the actorThatOpens is in the Volume
	if (pressurePlate && pressurePlate->IsOverlappingActor(actorThatOpens))
	{
		OpenDoor();
	}
	
}

