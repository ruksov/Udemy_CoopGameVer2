// Study Shooter Game from Udemy. All Rights Reserved.


#include "AI/Components/SGAIPerceptionComponent.h"
#include "AIController.h"
#include "SGUtils.h"
#include "Components/SGHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* USGAIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor*> PercieveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
    if (0 == PercieveActors.Num())
    {
        return nullptr;
    }

    const AAIController* Controller = Cast<AAIController>(GetOwner());
    const APawn* Pawn = Controller ? Controller->GetPawn() : nullptr;
    if (!Pawn)
    {
        return nullptr;
    }

    float MinDistance = MAX_FLT;
    AActor* ClosestActor = nullptr;
    for (AActor* Actor : PercieveActors)
    {
        const USGHealthComponent* HealthComponent = Actor->FindComponentByClass<USGHealthComponent>();
        if (!HealthComponent || HealthComponent->IsDead())
        {
            continue;
        }

        const float CurrentDistance = (Actor->GetActorLocation() - Pawn->GetActorLocation()).Size();
        if (CurrentDistance < MinDistance)
        {
            MinDistance = CurrentDistance;
            ClosestActor = Actor;
        }
    }

    return ClosestActor;
}
