// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Mortar.h"


// Sets default values
AMortar::AMortar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMortar::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = InitialHealth;
}

float AMortar::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent,
                        class AController* EventInstigator, AActor* DamageCauser){
    int32 Damage = FPlatformMath::RoundToInt(DamageAmount);
    int32 DamageToApply = FMath::Clamp(Damage, 0, CurrentHealth);
    
    CurrentHealth -= DamageToApply;
    if(CurrentHealth <= 0){
        UE_LOG(LogTemp, Warning, TEXT("Mortar DIES"));
        Destroy();
    }
    return DamageToApply;
}

float AMortar::GetHealthPercent() const{
    return (float)CurrentHealth / (float)InitialHealth;
}
