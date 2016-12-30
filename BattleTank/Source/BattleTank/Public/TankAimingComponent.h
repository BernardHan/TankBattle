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
	
private:
    // Sets default values for this component's properties
    UTankAimingComponent();
    
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    
    UPROPERTY(EditAnywhere, Category = Firing)
    float LaunchSpeed = 7000;

protected:
    UPROPERTY(BlueprintReadOnly, Category = State)
    EAimingState AimingState = EAimingState::Reloading; // initialize enum state to reloading
};
