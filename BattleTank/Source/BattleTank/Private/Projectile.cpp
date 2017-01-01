// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
    
    CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
    SetRootComponent(CollisionMesh); // set this as the root of the component
    CollisionMesh->SetNotifyRigidBodyCollision(true); // this makes the mesh generate hit event by default
    CollisionMesh->SetVisibility(false);
    
    LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
    LaunchBlast->AttachTo(RootComponent);
    
    ProjectileMovement->bAutoActivate = false; // make the projectile not fly off until we fire it

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


void AProjectile::Launch(float LaunchSpeed){
    ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * LaunchSpeed); // set the velocity
    ProjectileMovement->Activate(); // let it fly!
}
