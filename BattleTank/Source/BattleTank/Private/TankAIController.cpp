// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"



void ATankAIController::BeginPlay(){
    Super::BeginPlay();
}

// this method is a safe proof that even if when beginplay tank is not possessed, this method solves the mastter
void ATankAIController::SetPawn(APawn* InPawn){
    Super::SetPawn(InPawn);
    if(!InPawn) {return;}
    PossessedTank = Cast<ATank>(InPawn);
    if(!ensure(PossessedTank)){return;}
    
    // subscribe local method to the tank death event
    PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
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
        
        // if aiming locked, fire
        if(TankAimingComponent->GetAimingState() == EAimingState::Locked){
            TankAimingComponent->Fire();
        }
    }
}

void ATankAIController::OnTankDeath(){
    if(!PossessedTank) { return; }
    PossessedTank->DetachFromControllerPendingDestroy();
}
