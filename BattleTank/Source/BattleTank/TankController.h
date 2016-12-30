// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankController.generated.h" // must be the last to include


class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankController : public APlayerController
{
	GENERATED_BODY()
	
public:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
protected:
    void Aim(); // move the tank barrel so that the shot hits where the white point pointing to
    
    UFUNCTION(BlueprintImplementableEvent, Category = Setup)
    void FindAimingComponent(UTankAimingComponent* Referece);
    
private:
    //return the hit location if there's a hit
    bool RayHit(FVector& HitLocation) const; //const because it only return a vector and bool, no change to the tank
    
    UPROPERTY(EditAnywhere)
    float CrosshairXLoc = 0.5;
    UPROPERTY(EditAnywhere)
    float CrosshairYLoc = 0.2;
    
    float LineTraceRange = 1000000.f;
    
    bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
