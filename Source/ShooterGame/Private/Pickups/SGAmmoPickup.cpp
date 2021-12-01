// Study Shooter Game from Udemy. All Rights Reserved.


#include "Pickups/SGAmmoPickup.h"
#include "SGUtils.h"
#include "Components/SGHealthComponent.h"
#include "Components/SGWeaponComponent.h"

bool ASGAmmoPickup::ApplyPickupTo(APawn* Pawn)
{
    const USGHealthComponent* HealthComponent = SGUtils::GetPlayerComponentByClass<USGHealthComponent>(Pawn);
    if (!HealthComponent || HealthComponent->IsDead())
    {
        return false;
    }

    USGWeaponComponent* WeaponComponent = SGUtils::GetPlayerComponentByClass<USGWeaponComponent>(Pawn);
    return WeaponComponent && WeaponComponent->TryAddAmmo(WeaponType, ClipsAmount);
}
