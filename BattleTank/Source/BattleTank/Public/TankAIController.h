// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIController.h"
#include "TankAIController.generated.h"


class ATank;
/**
 * 
 */

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
    virtual void Tick(float DeltaSeconds) override;
private:
    virtual void BeginPlay() override;
    
    virtual void SetPawn(APawn* InPawn) override; // when ai controller gets possessed, then call this: get called when the pawn is possessed
    
    // delegate:
    UFUNCTION()
    void OnTankDeath();
    
    ATank* PossessedTank = nullptr;
    
protected:
    UPROPERTY(EditAnywhere, Category=Setup)
    float Radius = 8000; // the ai tanks stop at 80 meters away from player
    
    
};
