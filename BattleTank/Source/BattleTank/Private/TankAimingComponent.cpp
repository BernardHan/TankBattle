// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "Projectile.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	//Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
	
}


void UTankAimingComponent::SetAiming(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet){
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	//Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	bool ReloadReady = (FPlatformTime::Seconds() - LastFireTime) >= ReloadTime;
    
    if(AmmoLeft <= 0){
        AimingState = EAimingState::NoAmmo;
    }
    else if(!ReloadReady){
        AimingState = EAimingState::Reloading;
    }
    else if(IsBarrelMoving()){
        AimingState = EAimingState::Aiming;
    }
    else{
        AimingState = EAimingState::Locked;
    }
}

void UTankAimingComponent::AimAt(FVector HitLocation){
    if(!ensure(Barrel)){return;}
    auto BarrelLoc = Barrel->GetComponentLocation();
    //UE_LOG(LogTemp,Warning, TEXT("%s aiming at %s from %s"), *GetOwner()->GetName(), *HitLocation.ToString(), *BarrelLoc.ToString());
    
    // using suggest projectile velocity
    FVector OutVelocity; // the out param
    FVector Start = Barrel->GetSocketLocation(FName("FireOut"));
    
    bool Suggest = UGameplayStatics::SuggestProjectileVelocity(this, OutVelocity, Start, HitLocation, LaunchSpeed, false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace);
    
    
    if(Suggest){
        // turn the velocity to normalized direction
        AimDirection = OutVelocity.GetSafeNormal();
        //UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString());
        
        MoveBarrel(); //this move barrel pitch, and turret yaw, which move barrel also
    }
}

void UTankAimingComponent::MoveBarrel(){
    if(!ensure(Barrel && Turret)) { return; }
    
    // calculate the difference rotation between current and aim
    FRotator BarrelRot = Barrel->GetForwardVector().Rotation();
    FRotator AimRot = AimDirection.Rotation();
    FRotator Delta = AimRot - BarrelRot;
    
    // move the barrel according to frame rate
    Barrel->Elevate(Delta.Pitch);

    if(FMath::Abs(Delta.Yaw) < 180){
        Turret->TurretRotator(Delta.Yaw);
    }
    else{
        Turret->TurretRotator(-Delta.Yaw);
    }
    
}

bool UTankAimingComponent::IsBarrelMoving(){
    if(!ensure(Barrel)){ return false; }
    auto BarrelForward = Barrel->GetForwardVector();
    return !BarrelForward.Equals(AimDirection, 0.01); // if equal, then not aiming
}

void UTankAimingComponent::Fire(){
    
    // detect if reload ready
    //
    
    if(AimingState == EAimingState::Reloading || AimingState == EAimingState::NoAmmo) {return;}
    
    
    if(!ensure(Barrel)) { return;}
    if(!ensure(ProjectileBP)){return;}
    
    // instantiate a projectile at the location of socket "fireon"
    auto Projectile = GetWorld()->SpawnActor<AProjectile>(
                                                          ProjectileBP,
                                                          Barrel->GetSocketLocation(FName("FireOut")),
                                                          Barrel->GetSocketRotation(FName("FireOut"))
                                                          );
    
    Projectile->Launch(LaunchSpeed);
    LastFireTime = FPlatformTime::Seconds();
    
    AmmoLeft--;

}

EAimingState UTankAimingComponent::GetAimingState() const{
    return AimingState;
}

int UTankAimingComponent::GetAmmoLeft() const{
    return AmmoLeft;
}
