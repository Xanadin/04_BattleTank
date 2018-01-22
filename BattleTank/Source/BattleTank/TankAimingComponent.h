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
class AProjectile;

/**
* Trajectory calculation and firing
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitComponent();

protected:

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus mFiringStatus = EFiringStatus::Reloading;

private:
	void BeginPlay() override;
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")	// DefaultsOnly means you can edit only on the archetype and not on individual instances
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankBarrel* mBarrel = nullptr;
	UTankTurret* mTurret = nullptr;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 4000.0f;

	UPROPERTY(EditAnywhere, Category = "Firing") // EditAnywhere means you can have different values on individual instances
	float mReloadTimeInSeconds = 3;

	void MoveBarrel(FVector AimVector);

	double mLastFireTime = 0;
	FVector mAimDirection = FVector::ZeroVector;
};
