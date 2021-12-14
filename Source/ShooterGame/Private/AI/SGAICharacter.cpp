// Study Shooter Game from Udemy. All Rights Reserved.


#include "AI/SGAICharacter.h"
#include "AI/SGAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AI/Components/SGAIWeaponComponent.h"
#include "BrainComponent.h"

ASGAICharacter::ASGAICharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USGAIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ASGAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
    {
        MovementComponent->bUseControllerDesiredRotation = true;
        MovementComponent->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }
}

void ASGAICharacter::OnDeath()
{
    const AAIController* AIController = Cast<AAIController>(Controller);
    if (AIController && AIController->BrainComponent)
    {
        AIController->BrainComponent->Cleanup();
    }

    Super::OnDeath();
}
