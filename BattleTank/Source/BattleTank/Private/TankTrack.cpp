// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"



// this make one of the track move
void UTankTrack::SetThrottle(float Throttle){
    // Apply force
    auto Force = GetForwardVector() * Throttle * MaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); // the Tank root, which is below TankBP
    TankRoot->AddForceAtLocation(Force, ForceLocation);
}
