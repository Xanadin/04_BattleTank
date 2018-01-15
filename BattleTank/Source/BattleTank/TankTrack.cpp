// Nessun copyright, sto facendo solo pratica

#include "TankTrack.h" // Required as FIRST include in 4.17+ versions

void UTankTrack::SetThrottle(float Throttle)
{
	// TODO clamp actual throttle value
	FVector forceApplied = GetForwardVector() * Throttle * mMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	UPrimitiveComponent* tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
	return;
}




