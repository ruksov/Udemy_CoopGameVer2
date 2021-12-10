// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SGAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API ASGAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
    virtual void OnPossess(APawn* InPawn) override;

};
