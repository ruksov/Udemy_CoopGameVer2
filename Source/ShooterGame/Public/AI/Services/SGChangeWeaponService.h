// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SGChangeWeaponService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API USGChangeWeaponService : public UBTService
{
	GENERATED_BODY()
	
public:
    USGChangeWeaponService();

protected:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float Probability = 0.5f;
};
