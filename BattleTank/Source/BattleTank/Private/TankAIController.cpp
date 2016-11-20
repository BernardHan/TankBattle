// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay(){
    Super::BeginPlay();
    
    
    auto ControlledTank = GetControlledTank();
    auto PlayerTank = GetPlayerTank();
    if(!PlayerTank) {
        UE_LOG(LogTemp, Warning, TEXT("No Target."));
        
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Targeting: %s"), *(PlayerTank->GetName()));
    }
    
    
    
}

ATank* ATankAIController::GetControlledTank() const{
    
    return Cast<ATank>(GetPawn()); // get pawn give you the tank pawn under controlled, cast it from APawn* to ATank*s
}


ATank* ATankAIController::GetPlayerTank() const{
    
    ATank* Player = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if(!Player) {return nullptr;}
    
    return Player;
}
