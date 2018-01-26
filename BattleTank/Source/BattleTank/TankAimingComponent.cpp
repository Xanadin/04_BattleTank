// Nessun copyright, sto facendo solo pratica

#include "TankAimingComponent.h" // Required as FIRST include in 4.17+ versions
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	mLastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::InitComponent()
{
	mTurret = GetOwner()->FindComponentByClass<UTankTurret>();
	mBarrel = GetOwner()->FindComponentByClass<UTankBarrel>();
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return mFiringStatus;
}

int UTankAimingComponent::GetAmmo() const
{
	return mAmmo;
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!ensure(mBarrel)) { return; }
	if (mAmmo <= 0)
	{
		mFiringStatus = EFiringStatus::NoAmmo;
	}
	else if ((FPlatformTime::Seconds() - mLastFireTime) < mReloadTimeInSeconds)
	{
		mFiringStatus = EFiringStatus::Reloading;
	}
	else if ( mBarrel->GetForwardVector().Equals(mAimDirection, 0.1f) == false )
	{
		mFiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		mFiringStatus = EFiringStatus::Locked;
	}
	return;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
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
		mAimDirection = launchVelocity.GetSafeNormal();
		MoveBarrel(mAimDirection);
	}
	else
	{
	}
	return;
}

void UTankAimingComponent::MoveBarrel(FVector AimVector)
{
	// Find angle between barrel direction and launch direction
	if (!ensure(mBarrel)) return;
	if (!ensure(mTurret)) return;
	auto BarrelRotator = mBarrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimVector.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	mBarrel->Elevate(DeltaRotator.Pitch);
	float yaw = DeltaRotator.Yaw;
	
	if (yaw >= 180) { yaw -= 360; }
	if (yaw <= -180) { yaw += 360; }
	UE_LOG(LogTemp, Warning, TEXT("Yaw : %f"), yaw);
	mTurret->Rotate(yaw);
}

void UTankAimingComponent::Fire()
{
	if (!(ensure(mBarrel))) { return; }
	if (!(ensure(ProjectileBlueprint))) { return; }
	if ((mFiringStatus == EFiringStatus::Locked) || (mFiringStatus == EFiringStatus::Aiming))
	{
		auto projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			mBarrel->GetSocketLocation(FName(TEXT("Projectile"))),
			mBarrel->GetSocketRotation(FName(TEXT("Projectile"))));
		projectile->LaunchProjectile(LaunchSpeed);
		mLastFireTime = FPlatformTime::Seconds();
		mAmmo--;
	}
	return;
}