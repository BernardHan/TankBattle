// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
    ProjectileMovement->bAutoActivate = false; // make the projectile not fly off until we fire it
    
    CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
    SetRootComponent(CollisionMesh); // set this as the root of the component
    CollisionMesh->SetNotifyRigidBodyCollision(true); // this makes the mesh generate hit event by default
    CollisionMesh->SetVisibility(false);
    
    LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
    LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    
    ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
    ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    ImpactBlast->bAutoActivate = false;
    
    ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
    ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
    CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}


void AProjectile::Launch(float LaunchSpeed){
    ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * LaunchSpeed); // set the velocity
    ProjectileMovement->Activate(); // let it fly!
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
           UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit){
    

    LaunchBlast->Deactivate();
    ImpactBlast->Activate();
    ExplosionForce->FireImpulse();
    
    // destroy the projectle on hitting
    SetRootComponent(ImpactBlast); // keep the particle
    CollisionMesh->DestroyComponent();
    
    // detructor timer, so that won't be infinite projectiles in world outliner
    FTimerHandle Timer;
    GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimerExpire, DestroyDelay, false);
}

void AProjectile::OnTimerExpire(){
    Destroy();
}
