// Nessun copyright, sto facendo solo pratica

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"	// Must be the last include

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	UPROPERTY(EditAnywhere, Category = "Setup")
	int32 mStartingHealth = 100.0f;

private:
	int32 mCurrentHealth = mStartingHealth;
};
