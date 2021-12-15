// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "SGHealthPercentDecorator.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API USGHealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	USGHealthPercentDecorator();

protected:
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float HealthPercent = 0.6f;
};
