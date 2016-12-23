// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"



void UTankTurret::TurretRotator(float Degree){
    Degree = FMath::Clamp(Degree, -1.f, 1.f);
    auto change = Degree * MaxDegPerSec * GetWorld()->GetDeltaSeconds();
    auto newRot = RelativeRotation.Yaw + change;
    
    SetRelativeRotation(FRotator(0, newRot, 0));
}
