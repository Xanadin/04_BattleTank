// Nessun copyright, sto facendo solo pratica

#include "TankBarrel.h" // Required as FIRST include in 4.17+ versions
#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Rotate barrel some way to launch direction
	float verifiedSpeed = FMath::Clamp(RelativeSpeed, -1.0f, +1.0f);
	float elevationChange = verifiedSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float newElevation = RelativeRotation.Pitch + elevationChange;
	float clampedElevation = FMath::Clamp(newElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(clampedElevation, 0.0, 0.0));
	
	return;
}


