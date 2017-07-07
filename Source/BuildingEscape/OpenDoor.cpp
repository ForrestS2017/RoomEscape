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

	
	// ...
	
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	openDoor(DeltaTime);
	// ...
}

void UOpenDoor::openDoor(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("Opening Door"));
	FRotator NewRotation = FRotator(0.0f, 60.0f, 0.0f)*FMath::Sin(GetWorld()->TimeSeconds);
	//float NewRotation = 60.0f*FMath::Sin(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("Opening Door %s"), *(NewRotation.ToString()));
	Owner->SetActorRotation(NewRotation);
}
