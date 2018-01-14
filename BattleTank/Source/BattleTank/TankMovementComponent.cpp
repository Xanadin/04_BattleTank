// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h" // Required as FIRST include in 4.17+ versions
#include "TankTrack.h"

void UTankMovementComponent::InitializeComponent(UTankTrack* LeftTrack, UTankTrack* RightTrack)
{
	if (!LeftTrack || !RightTrack) return;
	mLeftTrack = LeftTrack;
	mRightTrack = RightTrack;
	return;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throw);
	mLeftTrack->SetThrottle(Throw); 
	mRightTrack->SetThrottle(Throw);
	// TODO Prevent double speed using double control
	return;
}


