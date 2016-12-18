// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankController.h"


void ATankController::BeginPlay(){
    Super::BeginPlay();
    
    
    ControlledTank = GetControlledTank();
    if(!ControlledTank) {
        UE_LOG(LogTemp, Warning, TEXT("TankController not possessed."));
    
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("TankController possessed by: %s"), *(ControlledTank->GetName()));
    }
    
    
    
}

ATank* ATankController::GetControlledTank() const{
    
    return Cast<ATank>(GetPawn()); // get pawn give you the tank pawn under controlled, cast it from APawn* to ATank*
}

void ATankController::Tick(float DeltaSeconds){
    Super::Tick(DeltaSeconds);
    Aim();
}

void ATankController::Aim(){
    if(!ControlledTank){return;}
    
    FVector HitLocation; // this is out parameter
    if(RayHit(HitLocation)){
        // call the AimAt method in Tank.cpp
        ControlledTank->AimAt(HitLocation);
    }

    
}

// if there is a hit, return true
bool ATankController::RayHit(FVector & HitLocation) const{
    // find the crosshair location
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    
    // get the screen location of the white dot
    auto DotLoc = FVector2D(ViewportSizeX * CrosshairXLoc, ViewportSizeY * CrosshairYLoc);
    
    //deproject the screen position of the dot in term of the world direction
    FVector CameraWorldLocation; // dummy vector for deproject function, we don't need it, but the function has to have it
    FVector WorldDirection;
    if(DeprojectScreenPositionToWorld(DotLoc.X, DotLoc.Y, CameraWorldLocation, WorldDirection)){
        
        // Now test if the look direction hit anything
        return GetLookVectorHitLocation(WorldDirection, HitLocation);
    }
    
    return false;
}

bool ATankController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const{
    FHitResult HitResult;
    auto Start = PlayerCameraManager->GetCameraLocation(); // start location ofthe line trace
    auto End = Start + LookDirection * LineTraceRange; // end location
    
    if(GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility)){
        // collision: hit anything that is visible
        // if line trace succeed
        // set the hitlocation
        HitLocation = HitResult.Location;
        //UE_LOG(LogTemp, Warning, TEXT("Target: %s"), *HitResult.GetActor()->GetName());
        //DrawDebugLine(GetWorld(), HitResult.TraceStart, HitResult.TraceEnd, FColor::Red);
        return true;
    }
    else{
        // otherwise
        return false;
    }
    
}
