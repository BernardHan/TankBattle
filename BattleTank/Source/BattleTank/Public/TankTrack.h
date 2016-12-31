// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
    UFUNCTION(BlueprintCallable, Category=Input)
    void SetThrottle(float Throttle);
    UPROPERTY(EditDefaultsOnly)
    float MaxDrivingForce = 40000000; //assume 40000kg, 10 acceleration
    
    // Called every frame
    //virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	
    virtual void BeginPlay() override;
    
private:
    UTankTrack();
    
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
               UPrimitiveComponent* OtherComponent, FVector NormalImpulse,
               const FHitResult& Hit);
    
    void CancelSideWay();
    
    void DriveTrack();
    
    float CurrentThrottle = 0; // cache throttke
};
