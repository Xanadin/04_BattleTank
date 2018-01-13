// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h" // Required as FIRST include in 4.17+ versions
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// Rotate turret some way to launch direction
	float verifiedSpeed = FMath::Clamp(RelativeSpeed, -1.0f, +1.0f);
	float azimuthChange = verifiedSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float newAzimuth = RelativeRotation.Yaw + azimuthChange;
	SetRelativeRotation(FRotator( 0.0, newAzimuth, 0.0 ));
	return;
}
