// Study Shooter Game from Udemy. All Rights Reserved.


#include "AI/Services/SGFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Components/SGWeaponComponent.h"

USGFireService::USGFireService()
{
    NodeName = "Fire";
}

void USGFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const AAIController* Controller = OwnerComp.GetAIOwner();
    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

    const bool HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

    const APawn* Pawn = Controller ? Controller->GetPawn() : nullptr;
    if (Pawn)
    {
        if (USGWeaponComponent* WeaponComponent = Pawn->FindComponentByClass<USGWeaponComponent>())
        {
            if (HasAim)
            {
                WeaponComponent->StartFire();
            }
            else
            {
                WeaponComponent->StopFire();
            }
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
