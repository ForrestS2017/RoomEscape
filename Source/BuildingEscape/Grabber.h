// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// Ray-cast and grab what's in reach
	void Grab();
	void Release();
	
	//Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	//Distance line trace should reach
	UPROPERTY(EditAnywhere)
	float reach = 200.0f;

private:

	

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;

	//BeginPlay Setups
	void FindPhysicsHandleComponent();
	void SetupAttatchedInputComponent();

	FVector GetLineReachEnd();

	
};
