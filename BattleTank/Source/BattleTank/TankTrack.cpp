// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h" // Required as FIRST include in 4.17+ versions

void UTankTrack::SetThrottle(float Throttle)
{

	UE_LOG(LogTemp, Warning, TEXT("%s throttle : %f"), *GetName(), Throttle);
	// TODO clamp actual throttle value
	FVector forceApplied = GetForwardVector() * Throttle * mMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	UPrimitiveComponent* tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
	return;
}




