// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor();
	void CloseDoor();

	virtual void BeginPlay() override;

private:
	// Any data member under UPROPERTY(VisibleAnywhere) becomes visibe in the engine
	UPROPERTY(EditAnywhere) 

	//The angle of the door's rotation
	float doorRotationAngle = -90.0f;

	// Any data member under UPROPERTY(EditAnywhere) becomes visibe, and can be edited in the engine
	UPROPERTY(EditAnywhere) 
	ATriggerVolume* pressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	//The time before the door is closed
	float doorClosedelay = 1.0f;

	//The time it took the door to open
	float lastDoorOpenTime; 

	UPROPERTY(BlueprintAssignable)
	FOnOpenRequest onOpenRequest;

	//The owning actor
	AActor* owner = nullptr;

	//returns total mass in kg
	float GetTotalMassOfActorsOnPlate();
};
