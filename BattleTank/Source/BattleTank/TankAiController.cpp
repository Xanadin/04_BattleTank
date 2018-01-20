// Nessun copyright, sto facendo solo pratica

#include "TankAiController.h" // Required as FIRST include in 4.17+ versions
#include "Engine/World.h"
#include "Tank.h"
#include "TankAimingComponent.h"
// Depends on the movement controller via pathfinding

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
	auto controlledPawn = GetPawn();
	if (controlledPawn != nullptr)
	{
		mControlledTank = Cast<ATank>(controlledPawn);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing pawn on AI controller"));
	}
	mAimingComponent = mControlledTank->FindComponentByClass<UTankAimingComponent>();
	return;
}

void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!ensure(mAimingComponent) || !ensure(mControlledTank)) return;
	ATank* playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (playerTank)
	{
		// Move towards the player
		MoveToActor(playerTank, mAcceptanceRadius); // TODO check radius is in centimeters

		// Fire at player
		mAimingComponent->AimAt(playerTank->GetActorLocation());
		mControlledTank->Fire(); // TODO don't fire every frame
	}
	return;
}