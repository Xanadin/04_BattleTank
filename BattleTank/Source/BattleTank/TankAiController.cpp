// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "Engine/World.h"

void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Move towards the player
	if (!mControlledTank) return;
	mControlledTank->AimAt(GetPlayerControlledTank()->GetActorLocation());
	// Fire if ready
}

ATank* ATankAiController::GetControlledTank() const
{
	auto controlledPawn = GetPawn();
	if (controlledPawn != nullptr)
	{
		ATank* controlledTank = Cast<ATank>(controlledPawn);
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
