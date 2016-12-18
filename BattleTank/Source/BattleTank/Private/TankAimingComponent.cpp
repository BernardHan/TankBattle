// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"


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
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed){
    if(!Barrel){return;}
    auto BarrelLoc = Barrel->GetComponentLocation();
    //UE_LOG(LogTemp,Warning, TEXT("%s aiming at %s from %s"), *GetOwner()->GetName(), *HitLocation.ToString(), *BarrelLoc.ToString());
    
    // using suggest projectile velocity
    FVector OutVelocity; // the out param
    FVector Start = Barrel->GetSocketLocation(FName("FireOut"));
    
    bool Suggest = UGameplayStatics::SuggestProjectileVelocity(this, OutVelocity, Start, HitLocation, LaunchSpeed);
    
    
    if(Suggest){
        // turn the velocity to normalized direction
        auto AimDirection = OutVelocity.GetSafeNormal();
        UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString());
        MoveBarrel(AimDirection);
    }
}

void UTankAimingComponent::SetBarrel(UStaticMeshComponent* BarrelToSet){
    Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection){
    // calculate the difference rotation between current and aim
    //FRotator BarrelRot = Barrel->GetComponentRotation();
    FRotator BarrelRot = Barrel->GetForwardVector().Rotation();
    FRotator AimRot = AimDirection.Rotation();
    FRotator Delta = AimRot - BarrelRot;
    
    // move the barrel according to frame rate
    
    
    
}
