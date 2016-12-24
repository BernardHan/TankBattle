// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
    void AimAt(FVector HitLocation);
    UFUNCTION(BlueprintCallable, Category = Setup)
    void SetBarrel(UTankBarrel* BarrelToSet);
    UFUNCTION(BlueprintCallable, Category = Setup)
    void SetTurret(UTankTurret* TurretToSet);
    
    UFUNCTION(BlueprintCallable, Category = Setup)
    void Fire();

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    
    // the projectile launch speed
    UPROPERTY(EditAnywhere, Category = Firing)
    float LaunchSpeed = 7000;
    
    UPROPERTY(EditAnywhere, Category = Setup)
    TSubclassOf<AProjectile> ProjectileBP;
    
    // keep a local referece of barrel so that we can spawn projectile
    UTankBarrel* Barrel = nullptr;
    
    float ReloadTime = 3.f; // 3 secs
    double LastFireTime = 0; // the time when it fires last time

protected:
    UTankAimingComponent* TankAimingComponent = nullptr;
	
	
};
