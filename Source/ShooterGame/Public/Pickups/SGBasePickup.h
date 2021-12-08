// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGBasePickup.generated.h"

class USphereComponent;

UCLASS()
class SHOOTERGAME_API ASGBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ASGBasePickup();

protected:
	virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
    virtual bool ApplyPickupTo(APawn* Pawn);

    void PickupWasTaken();
    void Respawn();

    void GenerateRotationPeriod();
    void Rotate(float DeltaSeconds);

protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent* CollisionComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup")
    float InitCollisionRadius = 50.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime = 5.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup")
    float RotationPeriodMinInSec = 2.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup")
    float RotationPeriodMaxInSec = 3.0f;

private:
    float RotationYaw = 0.0f;
    float RotationPeriodInSec = 0.0f;
};
