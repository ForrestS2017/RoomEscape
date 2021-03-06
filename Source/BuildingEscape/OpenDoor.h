// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void openDoor(float DeltaTime);
	void closeDoor(float DeltaTime);

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnClose;

private:

	AActor* Owner = nullptr;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* pressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
		float openAngle = -90.0f;

	UPROPERTY(EditAnywhere)
		float triggerMass = 30.0f;

	float LastDoorOpenTime;

	float GetTotalMassOnPlate();
	
};
