// Nessun copyright, sto facendo solo pratica

#include "Projectile.h" // Required as FIRST include in 4.17+ versions
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	mCollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("CollisionMesh")));
	SetRootComponent(mCollisionMesh);
	// Check by default simulation generates hit events
	mCollisionMesh->SetNotifyRigidBodyCollision(true);
	mCollisionMesh->SetVisibility(false);

	mProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName(TEXT("Movement Component")));
	mProjectileMovement->bAutoActivate = false;

	mLaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("LaunchBlast")));
	mLaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	mInpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("InpactBlast")));
	mInpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	mInpactBlast->bAutoActivate = false;

	mExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName(TEXT("ExplosionForce")));
	mExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	if (!ensure(mCollisionMesh)) { return; }
	mCollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::LaunchProjectile(float Speed)
{
	if (!ensure(mProjectileMovement)) return;
	mProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	mProjectileMovement->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	if (!ensure(mLaunchBlast)) { return; }
	mLaunchBlast->Deactivate();
	if (!ensure(mInpactBlast)) { return; }
	mInpactBlast->Activate();
	if (!ensure(mExplosionForce)) { return; }
	mExplosionForce->FireImpulse();
	return;
}

