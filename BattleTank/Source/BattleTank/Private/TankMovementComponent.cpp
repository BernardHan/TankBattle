// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::SetTracks(UTankTrack* LeftToSet, UTankTrack* RightToSet){
    if(!ensure(LeftToSet && RightToSet)){ return;}
    
    LeftTrack = LeftToSet;
    RightTrack = RightToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw){
    if(!ensure(LeftTrack && RightTrack)){ return;}
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

//This turn the tank
void UTankMovementComponent::IntendTurn(float Throw){
    if(!ensure(LeftTrack && RightTrack)){ return;}
    RightTrack->SetThrottle(Throw);
    LeftTrack->SetThrottle(-Throw);
}


void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed){
    // no super because we completely override it
    // this method will be called by the MoveToActor() from AI controller
    auto Velocity = MoveVelocity.GetSafeNormal();
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    
    auto ForwardThrow = FVector::DotProduct(TankForward, Velocity); // for going forward and backward
    auto TurnThrow = FVector::CrossProduct(TankForward, Velocity).Z; // this is fvector, so take out the z
    
    IntendMoveForward(ForwardThrow);
    IntendTurn(TurnThrow);
}

