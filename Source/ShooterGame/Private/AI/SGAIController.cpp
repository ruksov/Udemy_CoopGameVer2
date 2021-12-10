// Study Shooter Game from Udemy. All Rights Reserved.


#include "AI/SGAIController.h"
#include "AI/SGAICharacter.h"

void ASGAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (const ASGAICharacter* AICharacter = Cast<ASGAICharacter>(InPawn))
    {
        RunBehaviorTree(AICharacter->BehaviorTreeAsset);
    }
}
