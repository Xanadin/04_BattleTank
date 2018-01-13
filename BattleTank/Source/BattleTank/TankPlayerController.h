// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"	// Must be the last include

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	ATank * mControlledTank = nullptr;
	ATank* GetControlledTank() const;

	// Raycast using UI element and move the turrer where crosshair intersect
	void AimTowardsCrosshair();

	// Get intersection of crosshair with world
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.3f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0f;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
