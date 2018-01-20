// Nessun copyright, sto facendo solo pratica

#include "TankPlayerController.h" // Required as FIRST include in 4.17+ versions
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto controlledPawn = GetPawn();
	if (controlledPawn != nullptr)
	{
		mControlledTank = Cast<ATank>(controlledPawn);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing pawn on player controller"));
		return;
	}
	mAimingComponent = mControlledTank->FindComponentByClass<UTankAimingComponent>();
	return;
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(mAimingComponent)) { return; }
	// Raycast and get world intersection
	FVector hitLocation;
	GetSightRayHitLocation(hitLocation);
	mAimingComponent->AimAt(hitLocation);
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
		HitLocation = FVector::ZeroVector;
		return false;
	}	
}
