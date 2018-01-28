// Nessun copyright, sto facendo solo pratica

#include "Projectile.h" // Required as FIRST include in 4.17+ versions
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mCollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("CollisionMesh")));
	SetRootComponent(mCollisionMesh);
	// Check by default simulation generates hit events
	mCollisionMesh->SetNotifyRigidBodyCollision(true);
	mCollisionMesh->SetVisibility(false);

	mProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName(TEXT("Movement Component")));
	mProjectileMovement->bAutoActivate = false;

	mLaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("LaunchBlast")));
	mLaunchBlast->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float Speed)
{
	if (!ensure(mProjectileMovement)) return;
	mProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	mProjectileMovement->Activate();
}

