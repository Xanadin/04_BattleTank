// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h" // Required as FIRST include in 4.17+ versions
#include "Engine/World.h"
#include "Tank.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	auto controlledPawn = GetPawn();
	if (controlledPawn != nullptr)
	{
		ATank* controlledTank = Cast<ATank>(controlledPawn);
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
	GetSightRayHitLocation(hitLocation);
	if(!mControlledTank) return;
	mControlledTank->AimAt(hitLocation);
	return;
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	// Find crosshair position in viewport pixel coordinates
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	auto screenLocation = FVector2D(CrossHairXLocation * viewportSizeX, CrossHairYLocation * viewportSizeY);
	FVector lookDirection;
	if (GetLookDirection(screenLocation, lookDirection))
	{
		return GetLookVectorHitLocation(lookDirection, HitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	// Camera position
	FVector cameraWorldLocation;
	FVector crosshairToCameraDirection;
	// "De-project the screen position of the crosshair to a world direction
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, cameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult rayCastHit;
	// Raycast
	FVector startLocation = PlayerCameraManager->GetCameraLocation();
	FVector lineTraceEnd = startLocation + LookDirection * LineTraceRange;
	if (GetWorld()->LineTraceSingleByChannel(rayCastHit, startLocation, lineTraceEnd, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = rayCastHit.Location;
		return true;
	}
	else
	{
		HitLocation = FVector(0.0f);
		return false;
	}	
}
