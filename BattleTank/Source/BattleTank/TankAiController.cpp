// Nessun copyright, sto facendo solo pratica

#include "TankAiController.h" // Required as FIRST include in 4.17+ versions
#include "Engine/World.h"
#include "TankAimingComponent.h"
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
		mAimingComponent->Fire(); // TODO don't fire every frame
	}
	return;
}