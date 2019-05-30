// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void BeginPlay() override;

private:
	// Any data member under UPROPERTY(EditAnywhere) becomes visibe, and can be edited in the engine
	UPROPERTY(EditAnywhere) 
	ATriggerVolume* pressurePlate = nullptr;

	//Mass of pressurePlate
	UPROPERTY(EditAnywhere)
	float triggerMass = 30.0f;

	//Event to open the door, exposed to blueprint
	UPROPERTY(BlueprintAssignable)
	FDoorEvent onOpen;
	
	//Event to close the door, exposed to blueprint
	UPROPERTY(BlueprintAssignable)
	FDoorEvent onClose;

	//The owning actor
	AActor* owner = nullptr;

	//returns total mass in kg
	float GetTotalMassOfActorsOnPlate();
};
