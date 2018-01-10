// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"	// Must be the last include

class UTankBarrel;
class UTankTurret;

// Trajectory calculation
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void AimAt(FVector HitLocation, float LaunchSpeed);

	void SetBarrel(UTankBarrel* Barrel);
	void SetTurret(UTankTurret* Turret);
protected:

private:

	UTankBarrel* mBarrel = nullptr;
	UTankTurret* mTurret = nullptr;

	void MoveBarrel(FVector AimVector);
};
