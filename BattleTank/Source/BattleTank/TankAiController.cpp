// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h" // Required as FIRST include in 4.17+ versions
#include "Engine/World.h"
#include "Tank.h"

void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Move towards the player
	if (!mControlledTank) return;
	mControlledTank->AimAt(GetPlayerControlledTank()->GetActorLocation());
	mControlledTank->Fire(); // TODO don't fire every frame
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
