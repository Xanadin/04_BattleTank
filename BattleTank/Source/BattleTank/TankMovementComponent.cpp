// Nessun copyright, sto facendo solo pratica

#include "TankMovementComponent.h" // Required as FIRST include in 4.17+ versions
#include "TankTrack.h"

void UTankMovementComponent::InitComponent(UTankTrack* LeftTrack, UTankTrack* RightTrack)
{
	mLeftTrack = LeftTrack;
	mRightTrack = RightTrack;
	return;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!mLeftTrack || !mRightTrack) return;
	mLeftTrack->SetThrottle(Throw); 
	mRightTrack->SetThrottle(Throw);
	// TODO Prevent double speed using double control
	return;
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!mLeftTrack || !mRightTrack) return;
	mLeftTrack->SetThrottle(Throw);
	mRightTrack->SetThrottle(-Throw);
	// TODO Prevent double speed using double control
	return;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector tankRight = GetOwner()->GetActorRightVector().GetSafeNormal();
	FVector forwardIntention = MoveVelocity.GetSafeNormal();

	float forwardThrow = FVector::DotProduct(forwardIntention, tankForward);
	float rightThrow = FVector::DotProduct(forwardIntention, tankRight);
	IntendMoveForward(forwardThrow);
	IntendTurnRight(rightThrow);
	return;
}


