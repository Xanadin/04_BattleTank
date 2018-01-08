// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "Engine/World.h"

ATank* ATankAiController::GetControlledTank() const
{
	auto controlledPawn = GetPawn();
	if (controlledPawn != nullptr)
	{
		ATank* controlledTank = Cast<ATank>(controlledPawn);
		UE_LOG(LogTemp, Warning, TEXT("TankPossessed AI is %s"), *(controlledTank->GetName()));
		return controlledTank;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing pawn on AI controller"));
		return nullptr;
	}
}

ATank * ATankAiController::GetPlayerControlledTank() const
{
	auto playerControlledPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (playerControlledPawn != nullptr)
	{
		ATank* playerControlledTank = Cast<ATank>(playerControlledPawn);
		UE_LOG(LogTemp, Warning, TEXT("TankPossessed AI %s has found player tank %s"), *(mControlledTank->GetName()), *(playerControlledTank->GetName()));
		return playerControlledTank;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find player tank"));
		return nullptr;
	}
}

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
	mControlledTank = GetControlledTank();
	GetPlayerControlledTank();
}
