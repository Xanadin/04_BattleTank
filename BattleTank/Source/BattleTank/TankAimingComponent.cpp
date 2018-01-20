// Nessun copyright, sto facendo solo pratica

#include "TankAimingComponent.h" // Required as FIRST include in 4.17+ versions
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::InitComponent(UTankTurret * Turret, UTankBarrel * Barrel)
{
	mTurret = Turret;
	mBarrel = Barrel;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!ensure(mBarrel)) return;
	FVector launchVelocity;
	FVector startLocation = mBarrel->GetSocketLocation(FName(TEXT("Projectile")));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this,
																		launchVelocity,
																		startLocation,
																		HitLocation,
																		LaunchSpeed,
																		false,
																		0,
																		0,
																		ESuggestProjVelocityTraceOption::DoNotTrace,
																		FCollisionResponseParams::DefaultResponseParam,
																		TArray<AActor*>(),
																		false);
	if (bHaveAimSolution)
	{
		FVector launchDirection = launchVelocity.GetSafeNormal();
		MoveBarrel(launchDirection);
	}
	else
	{
	}
	return;
}

void UTankAimingComponent::MoveBarrel(FVector AimVector)
{
	// Find angle between barrel direction and launch direction
	if (!ensure( mBarrel && mTurret )) return;
	auto BarrelRotator = mBarrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimVector.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	mBarrel->Elevate(DeltaRotator.Pitch);
	mTurret->Rotate(DeltaRotator.Yaw);
}
