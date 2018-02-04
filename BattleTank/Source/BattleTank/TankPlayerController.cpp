// Nessun copyright, sto facendo solo pratica

#include "TankPlayerController.h" // Required as FIRST include in 4.17+ versions
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto mControlledPawn = GetPawn();
	if (mControlledPawn != nullptr)
	{
		mAimingComponent = mControlledPawn->FindComponentByClass<UTankAimingComponent>();
		if (mAimingComponent != nullptr)
		{
			PassAimingComponent(mAimingComponent);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Missing AimingComponent on player controller"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing pawn on player controller"));
	}
	return;
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(mAimingComponent)) { return; }
	// Raycast and get world intersection
	FVector hitLocation;
	bool canShootAtLocation = GetSightRayHitLocation(hitLocation);
	if (canShootAtLocation)
	{
		mAimingComponent->AimAt(hitLocation);
	}
	return;
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	// Find crosshair position in viewport pixel coordinates
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	auto screenLocation = FVector2D(CrossHairXLocation * viewportSizeX, CrossHairYLocation * viewportSizeY);
	return GetLookVectorHitLocation(screenLocation, HitLocation);

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector2D ScreenLocation, FVector& HitLocation) const
{
	FHitResult rayCastHit;
	FVector lookDirection;
	FVector cameraWorldLocation;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, cameraWorldLocation, lookDirection))
	{ 
		// Raycast
		FVector startLocation = cameraWorldLocation;
		FVector lineTraceEnd = startLocation + lookDirection * LineTraceRange;
		if (GetWorld()->LineTraceSingleByChannel(rayCastHit, startLocation, lineTraceEnd, ECollisionChannel::ECC_Visibility))
		{
			HitLocation = rayCastHit.Location;
			return true;
		}
	}
	HitLocation = FVector::ZeroVector;
	return false;
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		// Subscribe our local method to the tank's death
		auto possessedTank = Cast<ATank>(InPawn);
		if (!ensure(possessedTank)) { return; }
		possessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}
	return;
}
