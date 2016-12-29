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
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

    void AimAt(FVector HitLocation, float LaunchSpeed);
    
    void SetBarrel(UTankBarrel* BarrelToSet);
    
    void MoveBarrel(FVector AimDirection);
    
    void SetTurret(UTankTurret* TurretToSet);
	
private:
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;

protected:
    UPROPERTY(BlueprintReadOnly, Category = State)
    EAimingState AimingState = EAimingState::Reloading; // initialize enum state to reloading
};
