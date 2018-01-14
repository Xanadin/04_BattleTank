// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h" // Required as FIRST include in 4.17+ versions
#include "TankTrack.h"

void UTankMovementComponent::InitializeComponent(UTankTrack* LeftTrack, UTankTrack* RightTrack)
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


