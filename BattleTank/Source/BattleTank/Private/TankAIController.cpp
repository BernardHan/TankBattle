// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankAIController.h"
#include "Tank.h"



void ATankAIController::BeginPlay(){
    Super::BeginPlay();
    
    
    ControlledTank = GetControlledTank();
    PlayerTank = GetPlayerTank();
    if(!PlayerTank) {
        UE_LOG(LogTemp, Warning, TEXT("No Target."));
        
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Targeting: %s"), *(PlayerTank->GetName()));
    }
}

void ATankAIController::Tick(float DeltaSeconds){
    Super::Tick(DeltaSeconds);
    
    if(PlayerTank){
        //Move toward the player
        
        //Aim at the player
        ControlledTank->AimAt(PlayerTank->GetActorLocation());
        
        // fire
        ControlledTank->Fire();
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
