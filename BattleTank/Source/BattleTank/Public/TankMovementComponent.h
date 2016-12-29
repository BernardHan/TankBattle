// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 *  for driving the tank tracks
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category=Input)
    void IntendMoveForward(float Throw);
    UFUNCTION(BlueprintCallable, Category=Input)
    void IntendTurn(float Throw);
    UFUNCTION(BlueprintCallable, Category=Setup)
    void SetTracks(UTankTrack* LeftToSet, UTankTrack* RightToSet);
    
    // override this method from nav movement engine code
    virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
    

	
private:
    UTankTrack * LeftTrack = nullptr;
    UTankTrack * RightTrack =nullptr;
    
    
};
