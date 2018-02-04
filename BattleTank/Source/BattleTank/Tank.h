// Nessun copyright, sto facendo solo pratica

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"	// Must be the last include

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathEvent);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	FDeathEvent OnDeath;

	// Returns current health as a percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health") // Blueprint correspondent of const function
	float GetHealthPercent() const;

	virtual void BeginPlay() override;

protected:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	UPROPERTY(EditAnywhere, Category = "Setup")
	int32 mStartingHealth = 100.0f;

private:
	int32 mCurrentHealth;
};
