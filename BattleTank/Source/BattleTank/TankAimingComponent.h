// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"	// Must be the last include

// Enum for aiming state
UENUM()
enum class EFiringStatus : uint8
{
	Locked,
	Aiming,
	Reloading
};

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
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitComponent();

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 4000.0f;
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus mFiringStatus = EFiringStatus::Aiming;

private:
	UTankBarrel* mBarrel = nullptr;
	UTankTurret* mTurret = nullptr;

	void MoveBarrel(FVector AimVector);
};
