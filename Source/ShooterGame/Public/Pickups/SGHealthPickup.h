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

};
