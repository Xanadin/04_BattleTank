// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"

ATank* ATankAiController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
	ATank* controlledTank = GetControlledTank();
	if (GetControlledTank() != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPossessed AI is %s"), *(controlledTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing pawn on AI controller"));
	}
}
