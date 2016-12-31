// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"


UTankTrack::UTankTrack(){
    PrimaryComponentTick.bCanEverTick = false;
    
}

void UTankTrack::BeginPlay(){
    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

// will be called as long as the tank is attached to something
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                       UPrimitiveComponent* OtherComponent, FVector NormalImpulse,
                       const FHitResult& Hit){
    
    // Drive the tracks
    DriveTrack();
    
    // Apply sideway cancel force
    CancelSideWay();
    
    // reset the current throttle so it can stop
    CurrentThrottle = 0;
}

// Called every frame, this is responsible for cancelling out the side way moving
void UTankTrack::CancelSideWay(){
    // calculate the slip speed
    auto SlipSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
    
    // calculate the requred acceleration for this frame to correct the side moving
    auto DeltaTime = GetWorld()->GetDeltaSeconds();
    auto CorrectionAcceleration = -SlipSpeed / DeltaTime * GetRightVector();
    
    // calculate the sideways F= m * a
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2; // /2 because 2 tracks
    TankRoot->AddForce(CorrectionForce);
}

// this make one of the track move
void UTankTrack::SetThrottle(float Throttle){
    CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack(){
    // Apply force
    auto Force = GetForwardVector() * CurrentThrottle * MaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); // the Tank root, which is below TankBP
    TankRoot->AddForceAtLocation(Force, ForceLocation);
}
