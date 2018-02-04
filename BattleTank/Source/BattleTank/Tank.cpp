// Nessun copyright, sto facendo solo pratica

#include "Tank.h" // Required as FIRST include in 4.17+ versions

// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;	// Tick() turned off
	mCurrentHealth = mStartingHealth;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	mCurrentHealth = mStartingHealth;
}

float ATank::GetHealthPercent() const
{
	return (float)mCurrentHealth / (float)mStartingHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 damagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 damageToApply = FMath::Clamp<int32>(damagePoints, 0, mCurrentHealth);
	mCurrentHealth -= damageToApply;
	if (mCurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}
	return damageToApply;
}

