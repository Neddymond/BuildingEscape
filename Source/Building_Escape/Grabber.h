// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called when the game starts
	virtual void BeginPlay() override;

private:
	//How ahead of the player can we reach in cm
	float reach = 100.0f;

	//Utility object for moving physics objects around
	UPhysicsHandleComponent* physicsHandle = nullptr;

	//Implememnt an actor for input binding
	UInputComponent* inputComponent = nullptr;

	//Ray-cast and grab what's in reach
	void Grab();

};