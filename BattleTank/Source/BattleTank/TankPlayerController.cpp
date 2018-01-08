// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	auto controlledPawn = GetPawn();
	if (controlledPawn != nullptr)
	{
		ATank* controlledTank = Cast<ATank>(controlledPawn);
		UE_LOG(LogTemp, Warning, TEXT("TankPossessed by player is %s"), *(controlledTank->GetName()));
		return controlledTank;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing pawn on player controller"));
		return nullptr;
	}
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	mControlledTank = GetControlledTank();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	
}

void ATankPlayerController::AimTowardsCrosshair()
{
	// Raycast and get world intersection
	// Trail the barrel rowards this point
	return;
}
