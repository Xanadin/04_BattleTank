// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	auto controlledPawn = GetPawn();
	if (controlledPawn != nullptr)
	{
		ATank* controlledTank = Cast<ATank>(controlledPawn);
		UE_LOG(LogTemp, Warning, TEXT("TankPossessed by player is %s"), *(controlledTank->GetName()));
		return controlledTank;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing pawn on player controller"));
		return nullptr;
	}
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	mControlledTank = GetControlledTank();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	
}

void ATankPlayerController::AimTowardsCrosshair()
{
	// Raycast and get world intersection
	FVector hitLocation;
	if (GetSightRayHitLocation(hitLocation))
	{ 
		UE_LOG(LogTemp, Warning, TEXT("HitLocation = %s"), *hitLocation.ToString());
	}
	// TODO Trail the barrel rowards this point
	return;
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	HitLocation = FVector(0.0f);
	// Get Ray start based on player position
	// GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(mPlayerViewpointLocation, mPlayerViewpointRotation);

	// Get Ray end based on line length (cannon reach)
	// mLineTraceEnd = mPlayerViewpointLocation + mPlayerViewpointRotation.Vector() * mReach;

	// Raycast
	// FCollisionQueryParams queryParams(FName(TEXT("")), false, GetOwner());
	// GetWorld()->LineTraceSingleByObjectType(HitLocation, mPlayerViewpointLocation, mLineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), queryParams);
	return true;
}
