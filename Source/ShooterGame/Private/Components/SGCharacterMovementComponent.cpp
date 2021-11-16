// Study Shooter Game from Udemy. All Rights Reserved.


#include "Components/SGCharacterMovementComponent.h"
#include "Player/SGBaseCharacter.h"

float USGCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const ASGBaseCharacter* Player = Cast<ASGBaseCharacter>(GetPawnOwner());
    return Player && Player->IsRunning() ? (MaxSpeed * RunModifier) : MaxSpeed;
}
