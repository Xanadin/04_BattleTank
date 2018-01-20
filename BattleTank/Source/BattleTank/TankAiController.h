// Nessun copyright, sto facendo solo pratica

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAiController.generated.h"	// Must be the last include

class ATank;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAiController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	ATank* mControlledTank = nullptr;
	UTankAimingComponent* mAimingComponent = nullptr;

	// How close the AI tank can get
	float mAcceptanceRadius = 3000;
};
