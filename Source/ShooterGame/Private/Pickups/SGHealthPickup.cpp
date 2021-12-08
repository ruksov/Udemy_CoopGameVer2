// Study Shooter Game from Udemy. All Rights Reserved.


#include "Pickups/SGHealthPickup.h"
#include "SGUtils.h"
#include "Components/SGHealthComponent.h"

bool ASGHealthPickup::ApplyPickupTo(APawn* Pawn)
{
    USGHealthComponent* HealthComponent = SGUtils::GetPlayerComponentByClass<USGHealthComponent>(Pawn);
    return HealthComponent && HealthComponent->TryAddHealth(HealthAmount);
}
