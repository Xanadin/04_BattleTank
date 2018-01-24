// Nessun copyright, sto facendo solo pratica

#include "TankTrack.h" // Required as FIRST include in 4.17+ versions
#include "Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	// Calculate sideways slippage speed
	float slippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	// Work-out the required acceleration this frame to correct
	auto deltaTime = GetWorld()->GetDeltaSeconds();
	FVector correctionAcceleration = -(slippageSpeed / deltaTime) * GetRightVector();
	auto bpRootComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector correctionForce = (bpRootComponent->GetMass() / 2) * correctionAcceleration; // 2 Tracks
	bpRootComponent->AddForce(correctionForce);
	
	mCurrentThrottle = 0.0f;
}

void UTankTrack::SetThrottle(float Throttle)
{
	mCurrentThrottle = FMath::Clamp<float>(mCurrentThrottle + Throttle, -1, +1);
	FVector forceApplied = GetForwardVector() * Throttle * mMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	UPrimitiveComponent* tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
	return;
}




