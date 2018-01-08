// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "AIController.h"
#include "TankAiController.generated.h"	// Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAiController : public AAIController
{
	GENERATED_BODY()

public:
	ATank* GetControlledTank() const;
	void BeginPlay() override;
	
	
};
