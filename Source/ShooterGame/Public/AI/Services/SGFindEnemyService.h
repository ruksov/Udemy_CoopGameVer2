// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SGFindEnemyService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API USGFindEnemyService : public UBTService
{
	GENERATED_BODY()
	
public:
	USGFindEnemyService();

protected:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;
};

