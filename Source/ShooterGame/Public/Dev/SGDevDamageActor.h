// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGDevDamageActor.generated.h"

UCLASS()
class SHOOTERGAME_API ASGDevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASGDevDamageActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SphereRadius = 300.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FColor SphereColor = FColor::Red;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool DoFullDamage = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UDamageType> DamageType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
