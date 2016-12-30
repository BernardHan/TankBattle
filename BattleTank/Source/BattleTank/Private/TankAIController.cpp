// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"




void ATankAIController::BeginPlay(){
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds){
    Super::Tick(DeltaSeconds);
    
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto ControlledTank = GetPawn();
    
    if(ensure(PlayerTank && ControlledTank)){
        //Move toward the player
        MoveToActor(PlayerTank, Radius);
        //Aim at the player
        auto TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
        TankAimingComponent->AimAt(PlayerTank->GetActorLocation());
        
        // fire
        //ControlledTank->Fire();
    }
}
