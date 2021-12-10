// Study Shooter Game from Udemy. All Rights Reserved.


#include "AI/SGAICharacter.h"
#include "AI/SGAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ASGAICharacter::ASGAICharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit)
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
