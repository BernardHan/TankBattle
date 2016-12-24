// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    
    // no need to protect pointer, if it fail, the constructor fails
    TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
    
    InputComponent->BindAction("Fire", IE_Pressed, this, &ATank::Fire);

}

void ATank::AimAt(FVector HitLocation){
    TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrel(UTankBarrel* BarrelToSet){
    TankAimingComponent->SetBarrel(BarrelToSet);
    Barrel = BarrelToSet;
}

void ATank::SetTurret(UTankTurret* TurretToSet){
    TankAimingComponent->SetTurret(TurretToSet);
}

void ATank::Fire(){
    
    // detect if reload ready
    bool ReloadReady = (FPlatformTime::Seconds() - LastFireTime) >= ReloadTime;
    
    if(!Barrel || !ReloadReady) {return;}
    
    
    
    
    // instantiate a projectile at the location of socket "fireon"
    auto Projectile = GetWorld()->SpawnActor<AProjectile>(
        ProjectileBP,
        Barrel->GetSocketLocation(FName("FireOut")),
        Barrel->GetSocketRotation(FName("FireOut"))
    );
    
    Projectile->Launch(LaunchSpeed);
    LastFireTime = FPlatformTime::Seconds();
}
