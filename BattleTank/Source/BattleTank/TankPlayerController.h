// Nessun copyright, sto facendo solo pratica

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"	// Must be the last include

class UTankAimingComponent;

/**
* Responsible for helping the player aim
*/
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void PassAimingComponent(UTankAimingComponent* AimingComponent);

private:
	APawn * mControlledPawn = nullptr;
	UTankAimingComponent* mAimingComponent = nullptr;

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

	bool GetLookVectorHitLocation(FVector2D ScreenLocation, FVector& HitLocation) const;
};
