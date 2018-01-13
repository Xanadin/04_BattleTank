// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Holds barrel properties and elevate method
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downwards movement and +1 is max upwards
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevationDegrees = 30.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevationDegrees = -1.0f;
};
