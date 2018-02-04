// Nessun copyright, sto facendo solo pratica

#include "TankAiController.h" // Required as FIRST include in 4.17+ versions
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"
// Depends on the movement controller via pathfinding

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
	mControlledPawn = GetPawn();
	if (mControlledPawn != nullptr)
	{
		mAimingComponent = mControlledPawn->FindComponentByClass<UTankAimingComponent>();
		if (mAimingComponent == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Missing pawn on AI controller"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing AimingComponent on AI controller"));
	}
	return;
}

void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!ensure(mAimingComponent)) { return; }
	if (!ensure(mControlledPawn)) { return; }
	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (playerTank)
	{
		// Move towards the player
		MoveToActor(playerTank, mAcceptanceRadius); // TODO check radius is in centimeters

		// Fire at player
		mAimingComponent->AimAt(playerTank->GetActorLocation());
		if (mAimingComponent->GetFiringStatus() == EFiringStatus::Locked)
		{
			mAimingComponent->Fire();
		}
		
	}
	return;
}

void ATankAiController::OnTankDeath()
{
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAiController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		// Subscribe our local method to the tank's death
		auto possessedTank = Cast<ATank>(InPawn);
		if (!ensure(possessedTank)) { return; }
		possessedTank->OnDeath.AddUniqueDynamic(this, &ATankAiController::OnTankDeath);
	}
	return;
}
