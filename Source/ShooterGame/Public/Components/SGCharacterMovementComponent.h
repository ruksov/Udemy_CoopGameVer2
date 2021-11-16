// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SGCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API USGCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "1.5", ClampMax = "10.0"))
	float RunModifier = 2.0f;

	float GetMaxSpeed() const override;
};
