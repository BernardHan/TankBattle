// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"


UTankTrack::UTankTrack(){
    PrimaryComponentTick.bCanEverTick = true;
}


// Called every frame, this is responsible for cancelling out the side way moving
void UTankTrack::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ){
    // calculate the slip speed
    auto SlipSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
    
    // calculate the requred acceleration for this frame to correct the side moving
    auto CorrectionAcceleration = -SlipSpeed / DeltaTime * GetRightVector();
    
    // calculate the sideways F= m * a
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2; // /2 because 2 tracks
    TankRoot->AddForce(CorrectionForce);
}

// this make one of the track move
void UTankTrack::SetThrottle(float Throttle){
    // Apply force
    auto Force = GetForwardVector() * Throttle * MaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); // the Tank root, which is below TankBP
    TankRoot->AddForceAtLocation(Force, ForceLocation);
}
