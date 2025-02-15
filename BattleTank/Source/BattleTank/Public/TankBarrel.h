// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    void Elevate(float Degree);
	
private:
    UPROPERTY(EditAnywhere, Category = Setup)
    float MaxDegPerSec = 15; //default
    UPROPERTY(EditAnywhere, Category = Setup)
    float MaxElevation = 40; //max 40 degree
    UPROPERTY(EditAnywhere, Category = Setup)
    float MinElevation = 0; //min 0degree
	
};
