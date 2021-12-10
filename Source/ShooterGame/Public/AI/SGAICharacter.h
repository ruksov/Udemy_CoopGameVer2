// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/SGBaseCharacter.h"
#include "SGAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class SHOOTERGAME_API ASGAICharacter : public ASGBaseCharacter
{
	GENERATED_BODY()
	
public:
    ASGAICharacter(const FObjectInitializer& ObjInit);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;
};
