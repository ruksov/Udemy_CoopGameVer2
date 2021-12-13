// Study Shooter Game from Udemy. All Rights Reserved.


#include "AI/SGAIController.h"
#include "AI/SGAICharacter.h"
#include "AI/Components/SGAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ASGAIController::ASGAIController()
{
    SGPerceptionComponent = CreateDefaultSubobject<USGAIPerceptionComponent>("SGPerceptionComponent");
    SetPerceptionComponent(*SGPerceptionComponent);
}

void ASGAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (const ASGAICharacter* AICharacter = Cast<ASGAICharacter>(InPawn))
    {
        RunBehaviorTree(AICharacter->BehaviorTreeAsset);
    }
}

void ASGAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AActor* AimActor = GetFocusOnActor();
    SetFocus(AimActor);
}

AActor* ASGAIController::GetFocusOnActor() const
{
    const UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
    return BlackboardComponent ? Cast<AActor>(BlackboardComponent->GetValueAsObject(FocusOnKeyName)) : nullptr;
}
