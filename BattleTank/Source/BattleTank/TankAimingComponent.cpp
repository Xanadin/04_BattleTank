// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h" // Required as FIRST include in 4.17+ versions
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;	// TODO Disable ticking ?

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
																		false,
																		0,
																		0,
																		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam, TArray<AActor*>(), true
																					);
	float time = GetWorld()->GetTimeSeconds();
	if (bHaveAimSolution)
	{
		FVector launchDirection = launchVelocity.GetSafeNormal();
		MoveBarrel(launchDirection);
		UE_LOG(LogTemp, Warning, TEXT("%f : Trajectory solution found"), time);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%f : Trajectory solution not found"), time);
	}
	return;
}

void UTankAimingComponent::SetBarrel(UTankBarrel * Barrel)
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
	mBarrel->Elevate(5.0f); // TODO remove magic number
}

