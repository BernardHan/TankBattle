// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EAimingState : uint8
{
    Reloading,
    Aiming,
    Locked
};


class UTankBarrel; // forward declaration
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

    void AimAt(FVector HitLocation);
    
    
    void MoveBarrel(FVector AimDirection);

    
    UFUNCTION(BlueprintCallable, Category = Setup)
    void SetAiming(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
    
    UFUNCTION(BlueprintCallable, Category = Setup)
    void Fire();
    
	
private:
    // Sets default values for this component's properties
    UTankAimingComponent();
    
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    
    // the projectile launch speed
    UPROPERTY(EditAnywhere, Category = Firing)
    float LaunchSpeed = 7000;
    
    UPROPERTY(EditAnywhere, Category = Setup)
    TSubclassOf<AProjectile> ProjectileBP;

    float ReloadTime = 3.f; // 3 secs
    double LastFireTime = 0; // the time when it fires last time

protected:
    UPROPERTY(BlueprintReadOnly, Category = State)
    EAimingState AimingState = EAimingState::Reloading; // initialize enum state to reloading
};
