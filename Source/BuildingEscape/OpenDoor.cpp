// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"


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

	Owner = GetOwner();
	openingActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	// ...
	
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	// Poll the Trigger Volume every frame
	if (pressurePlate->IsOverlappingActor(openingActor))
	{
		// If the openingActor is in the volume
		openDoor(DeltaTime);
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime >= DoorCloseDelay)
	{
		closeDoor(DeltaTime);
	}
	
	
	/*else {
		closeDoor(DeltaTime);
	}*/
	
	
}

void UOpenDoor::openDoor(float DeltaTime)
{
	float openRoll = FMath::Clamp((Owner->GetActorRotation().Yaw - 1.0f), openAngle, 0.f);
	FRotator NewRotation = FRotator(0.0f, openRoll, 0.0f);
	Owner->SetActorRotation(NewRotation);
}

void UOpenDoor::closeDoor(float DeltaTime)
{
	float openRoll = FMath::Clamp((Owner->GetActorRotation().Yaw + 1.0f), openAngle, 0.f);
	FRotator NewRotation = FRotator(0.0f, openRoll, 0.0f);
	Owner->SetActorRotation(NewRotation);
}
