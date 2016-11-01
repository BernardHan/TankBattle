// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankController.h"


void ATankController::BeginPlay(){
    Super::BeginPlay();
}

ATank* ATankController::GetControlledTank() const{
    
    return Cast<ATank>(GetPawn()); // get pawn give you the tank pawn under controlled, cast it from APawn* to ATank*
}
