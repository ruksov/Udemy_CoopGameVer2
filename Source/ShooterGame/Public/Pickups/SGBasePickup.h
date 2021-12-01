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
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
    virtual bool ApplyPickupTo(APawn* Pawn);

    void PickupWasTaken();
    void Respawn();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent* CollisionComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup")
    float InitCollisionRadius = 50.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime = 5.0f;
};
