// Study Shooter Game from Udemy. All Rights Reserved.


#include "AI/Tasks/SGNextLocationTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

USGNextLocationTask::USGNextLocationTask()
{
    NodeName = "Next Location";
}

EBTNodeResult::Type USGNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const AAIController* Controller = OwnerComp.GetAIOwner();
    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Controller || !Blackboard)
    {
        return EBTNodeResult::Failed;
    }

    APawn* Pawn = Controller->GetPawn();
    if (!Pawn)
    {
        return EBTNodeResult::Failed;
    }

    const UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(Pawn);
    if (!NavSys)
    {
        return EBTNodeResult::Failed;
    }

    FVector Location = Pawn->GetActorLocation();
    if (!SelfCenter)
    {
        const AActor* CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
        if (!CenterActor)
        {
            return EBTNodeResult::Failed;
        }
        Location = CenterActor->GetActorLocation();
    }

    FNavLocation NavLocation;
    const bool Found = NavSys->GetRandomReachablePointInRadius(Location, SearchRadius, NavLocation);
    if (!Found)
    {
        return EBTNodeResult::Failed;
    }

    Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);
    return EBTNodeResult::Succeeded;
}
