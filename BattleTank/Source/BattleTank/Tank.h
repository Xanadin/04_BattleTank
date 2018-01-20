// Nessun copyright, sto facendo solo pratica

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"	// Must be the last include

class UTankBarrel;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintCallable)
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// TODO remove once Fire is move to AimingComponent
	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 4000.0f;

	UPROPERTY(EditAnywhere, Category = "Firing") // EditAnywhere means you can have different values on individual instances
	float mReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")	// DefaultsOnly means you can edit only on the archetype and not on individual instances
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// Local reference for projectile spawning
	UTankBarrel* mBarrel = nullptr;	// TODO Remove

	double mLastFireTime = 0;
	
};
