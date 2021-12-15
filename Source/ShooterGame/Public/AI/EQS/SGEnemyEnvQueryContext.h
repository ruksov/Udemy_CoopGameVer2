// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "SGEnemyEnvQueryContext.generated.h"

UCLASS()
class SHOOTERGAME_API USGEnemyEnvQueryContext : public UEnvQueryContext
{
    GENERATED_BODY()

    virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName EnemyActorKeyName = "EnemyActor";
};
