// Nessun copyright, sto facendo solo pratica

#include "TankAiController.h" // Required as FIRST include in 4.17+ versions
#include "Engine/World.h"
#include "Tank.h"

void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!mControlledTank) return;
	ATank* playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (playerTank)
	{
		// Move towards the player
		MoveToActor(playerTank, mAcceptanceRadius); // TODO check radius is in centimeters
		// Fire at player
		mControlledTank->AimAt(playerTank->GetActorLocation());
		mControlledTank->Fire(); // TODO don't fire every frame
	}
	return;
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

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
	mControlledTank = GetControlledTank();
}
