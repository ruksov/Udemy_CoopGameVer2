// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SGBasePickup.h"
#include "SGAmmoPickup.generated.h"

class ASGBaseWeapon;

UCLASS()
class SHOOTERGAME_API ASGAmmoPickup : public ASGBasePickup
{
	GENERATED_BODY()
	
private:
    virtual bool ApplyPickupTo(APawn* Pawn) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1", ClampMax = "10"))
	int32 ClipsAmount = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TSubclassOf<ASGBaseWeapon> WeaponType;
};
