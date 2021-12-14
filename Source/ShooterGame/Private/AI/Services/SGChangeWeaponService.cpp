// Study Shooter Game from Udemy. All Rights Reserved.


#include "AI/Services/SGChangeWeaponService.h"
#include "AIController.h"
#include "Components/SGWeaponComponent.h"

USGChangeWeaponService::USGChangeWeaponService()
{
    NodeName = "Change Weapon";
}

void USGChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    if (FMath::FRand() < Probability)
    {
        const AAIController* Controller = OwnerComp.GetAIOwner();
        const APawn* Pawn = Controller ? Controller->GetPawn() : nullptr;

        if (USGWeaponComponent* WeaponComponent = Pawn->FindComponentByClass<USGWeaponComponent>())
        {
            WeaponComponent->NextWeapon();
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
