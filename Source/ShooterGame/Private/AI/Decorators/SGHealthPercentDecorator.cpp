// Study Shooter Game from Udemy. All Rights Reserved.


#include "AI/Decorators/SGHealthPercentDecorator.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"
#include "Components/SGHealthComponent.h"

USGHealthPercentDecorator::USGHealthPercentDecorator()
{
    NodeName = "Health Percent";
}

bool USGHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const AAIController* Controller = OwnerComp.GetAIOwner();
    const APawn* Pawn = Controller ? Controller->GetPawn() : nullptr;
    const USGHealthComponent* HealthComponent = Pawn ? Pawn->FindComponentByClass<USGHealthComponent>() : nullptr;
    
    if (!HealthComponent || HealthComponent->IsDead())
    {
        return false;
    }

    return HealthComponent->GetHealthRatio() <= HealthPercent;
}
