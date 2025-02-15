// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	//virtual void Tick( float DeltaSeconds ) override;
    
    void Launch(float LaunchSpeed);

private:
    UProjectileMovementComponent* ProjectileMovement = nullptr;
    
	UPROPERTY(VisibleAnywhere, Category = Component)
    UStaticMeshComponent* CollisionMesh = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category = Component)
    UParticleSystemComponent* LaunchBlast = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category = Component)
    UParticleSystemComponent* ImpactBlast = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category = Component)
    URadialForceComponent* ExplosionForce = nullptr;
    
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    float DestroyDelay = 3.f;
    
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    float BaseDamage = 20.f;
    
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
               UPrimitiveComponent* OtherComponent, FVector NormalImpulse,
               const FHitResult& Hit);
    
    void OnTimerExpire();
};
