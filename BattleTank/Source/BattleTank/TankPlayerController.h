// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"	// Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	ATank * mControlledTank = nullptr;
	ATank* GetControlledTank() const;

	// Raycast using UI element and move the turrer where crosshair intersect
	void AimTowardsCrosshair();

	// Get intersection of crosshair with world
	bool GetSightRayHitLocation(FVector& HitLocation) const;

};
