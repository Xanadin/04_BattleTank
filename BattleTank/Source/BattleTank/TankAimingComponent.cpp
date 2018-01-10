// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!mBarrel) return;
	FVector launchVelocity;
	FVector startLocation = mBarrel->GetSocketLocation(FName(TEXT("Projectile")));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this,
																		launchVelocity,
																		startLocation,
																		HitLocation,
																		LaunchSpeed,
																		ESuggestProjVelocityTraceOption::DoNotTrace);
	if (bHaveAimSolution)
	{
		FVector launchDirection = launchVelocity.GetSafeNormal();
		MoveBarrel(launchDirection);
		DrawDebugLine(GetWorld(), startLocation, HitLocation, FColor::Red);
	}
	return;
}

void UTankAimingComponent::SetBarrel(UStaticMeshComponent * Barrel)
{
	mBarrel = Barrel;
}

void UTankAimingComponent::MoveBarrel(FVector AimVector)
{
	// Find angle between barrel direction and launch direction
	if (!mBarrel) return;
	auto BarrelRotator = mBarrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimVector.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	// Rotate barrel some way to launch direction
}

