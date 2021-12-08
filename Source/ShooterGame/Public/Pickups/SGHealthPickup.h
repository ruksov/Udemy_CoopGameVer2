// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SGBasePickup.h"
#include "SGHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API ASGHealthPickup : public ASGBasePickup
{
	GENERATED_BODY()
	
private:
    virtual bool ApplyPickupTo(APawn* Pawn) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "0.0"))
    float HealthAmount = 50.0f;
};
