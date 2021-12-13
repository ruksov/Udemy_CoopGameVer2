// Study Shooter Game from Udemy. All Rights Reserved.


#include "AI/Services/SGFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "AI/Components/SGAIPerceptionComponent.h"

USGFindEnemyService::USGFindEnemyService()
{
    NodeName = "Find Enemy";
}

void USGFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    if (UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent())
    {
        const AAIController* Controller = OwnerComp.GetAIOwner();
        const USGAIPerceptionComponent* PerceptionComponent = Controller ? Controller->FindComponentByClass<USGAIPerceptionComponent>() : nullptr;
        if (PerceptionComponent)
        {
            Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
