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
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	// Tick() turned off
	mTankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName(TEXT("Aiming Component")));
}

void ATank::AimAt(FVector HitLocation)
{

	mTankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* Barrel)
{
	mBarrel = Barrel;
	mTankAimingComponent->SetBarrel(Barrel);
}

void ATank::SetTurretReference(UTankTurret * Turret)
{
	mTankAimingComponent->SetTurret(Turret);
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

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

