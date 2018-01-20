// Nessun copyright, sto facendo solo pratica

#include "Tank.h" // Required as FIRST include in 4.17+ versions
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "TankBarrel.h"

// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;	// Tick() turned off
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for BP BeginPlay to get called
	mTankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(mTankAimingComponent)) return;
	mTankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	if (!ensure(mBarrel)) { return; }
	bool isReloaded = (FPlatformTime::Seconds() - mLastFireTime) > mReloadTimeInSeconds;
	if ( isReloaded )
	{
		auto projectile = GetWorld()->SpawnActor<AProjectile>(	ProjectileBlueprint,
																mBarrel->GetSocketLocation(FName(TEXT("Projectile"))),
																mBarrel->GetSocketRotation(FName(TEXT("Projectile"))));
		projectile->LaunchProjectile(LaunchSpeed);
		mLastFireTime = FPlatformTime::Seconds();
	}
	return;
}