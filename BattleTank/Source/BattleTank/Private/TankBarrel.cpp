// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"




void UTankBarrel::Elevate(float Degree){
    Degree = FMath::Clamp(Degree, -1.f, 1.f);
    // move the barrel degree at this frame
    // give a max elevation speed, and frame time
    auto change = Degree * MaxDegPerSec * GetWorld()->GetDeltaSeconds();
    auto newRot = RelativeRotation.Pitch + change;
    newRot = FMath::Clamp<float>(newRot, MinElevation, MaxElevation);
    
    SetRelativeRotation(FRotator(newRot, 0, 0));
}
