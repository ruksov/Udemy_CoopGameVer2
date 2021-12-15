// Study Shooter Game from Udemy. All Rights Reserved.


#include "AI/EQS/SGEnemyEnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void USGEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
    AActor* QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());

    if (const UBlackboardComponent* Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner))
    {
        const AActor* ContextActor = Cast<AActor>(Blackboard->GetValueAsObject(EnemyActorKeyName));
        UEnvQueryItemType_Actor::SetContextHelper(ContextData, ContextActor);
    }
}