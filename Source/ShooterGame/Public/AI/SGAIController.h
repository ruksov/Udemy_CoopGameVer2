// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SGAIController.generated.h"

class USGAIPerceptionComponent;

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API ASGAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ASGAIController();

protected:
    virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

private:
	AActor* GetFocusOnActor() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USGAIPerceptionComponent* SGPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";
};
