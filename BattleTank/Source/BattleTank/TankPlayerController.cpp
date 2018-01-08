// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* controlledTank = GetControlledTank();
	if (GetControlledTank() != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPossessed by player is %s"), *(controlledTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing pawn on player controller"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}
