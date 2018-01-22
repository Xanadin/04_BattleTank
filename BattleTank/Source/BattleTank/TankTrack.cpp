// Nessun copyright, sto facendo solo pratica

#include "TankTrack.h" // Required as FIRST include in 4.17+ versions

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Calculate sideways slippage speed
	float slippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	// Work-out the required acceleration this frame to correct
	FVector correctionAcceleration = - (slippageSpeed / DeltaTime) * GetRightVector();
	auto bpRootComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector correctionForce = ( bpRootComponent->GetMass() / 2 ) * correctionAcceleration; // 2 Tracks
	bpRootComponent->AddForce(correctionForce);
	// Calculate and apply sideways force
	return;
}

void UTankTrack::SetThrottle(float Throttle)
{
	// TODO clamp actual throttle value
	FVector forceApplied = GetForwardVector() * Throttle * mMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	UPrimitiveComponent* tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
	return;
}




