// Nessun copyright, sto facendo solo pratica

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"	// Must be the last include

class UTankBarrel;
class UTankTurret;
class UTankTrack;
class AProjectile;
class UTankAimingComponent;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* Barrel);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* Turret);

	UFUNCTION(BlueprintCallable)
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* mTankAimingComponent = nullptr;
private:	

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 4000.0f;

	UPROPERTY(EditAnywhere, Category = Firing) // EditAnywhere means you can have different values on individual instances
	float mReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = Firing)	// DefaultsOnly means you can edit only on the archetype and not on individual instances
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Local reference for projectile spawning
	UTankBarrel* mBarrel = nullptr;

	double mLastFireTime = 0;
	
};
