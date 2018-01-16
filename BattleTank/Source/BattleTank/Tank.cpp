// Nessun copyright, sto facendo solo pratica

#include "Tank.h" // Required as FIRST include in 4.17+ versions
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "TankBarrel.h"

// Sets default values
ATank::ATank()
{
	UE_LOG(LogTemp, Warning, TEXT("DONKEY : Tank %s C++ constructor called"), *GetName());
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	// Tick() turned off
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("DONKEY : Tank %s C++ BeginPlay called"), *GetName());
	Super::BeginPlay(); // Needed for BP BeginPlay to get called
}

void ATank::AimAt(FVector HitLocation)
{
	if (!mTankAimingComponent) return;
	mTankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - mLastFireTime) > mReloadTimeInSeconds;
	if ( mBarrel && isReloaded )
	{
		auto projectile = GetWorld()->SpawnActor<AProjectile>(	ProjectileBlueprint,
																mBarrel->GetSocketLocation(FName(TEXT("Projectile"))),
																mBarrel->GetSocketRotation(FName(TEXT("Projectile"))));
		projectile->LaunchProjectile(LaunchSpeed);
		mLastFireTime = FPlatformTime::Seconds();
	}
	return;
	// Spawn a projectile at socket location
	
}