// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupAttatchedInputComponent();
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	//If physics handle is attatched
		// move the object that we're holding


	/// Get player view Point this tick
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT playerViewPointLocation, OUT playerViewPointRotation);

	/// Draw debug line
	FVector LineTraceEnd = playerViewPointLocation + playerViewPointRotation.Vector()*reach;
	DrawDebugLine(GetWorld(), playerViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.0f, 0.0f, 10.0f);

	/// Get Hit result
	FHitResult LineTraceHit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT LineTraceHit, playerViewPointLocation, LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);
	AActor* HitResult = LineTraceHit.GetActor();
	if (HitResult) {
		UE_LOG(LogTemp, Warning, TEXT("Grabber Result: %s"), *(HitResult->GetName()));
	}
	
	// ...
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("GRABBED"));

	/// Try to reach any actors with physics body collision channel set

	// If we hit something, attach a physics handle

	// TODO: Attatch Physcis Handle
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("RELEASED"));

	// TODO: Release Physics handle
}

void UGrabber::FindPhysicsHandleComponent() 
{
	/// Look for attatched physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle)
	{
		//Physics handle found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Phy Hndl CMP: %s"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupAttatchedInputComponent() 
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Input component found"));
		//Bind input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Missing INPT CMP: %s"), *GetOwner()->GetName());
	}
}