// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SGHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAME_API USGHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USGHealthComponent();

	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return Health <= 0.0f; }

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetHealth(float Value);

private:
    UFUNCTION()
    void OnTakeAnyDamage(
        AActor* DamagedActor,
        float Damage,
        const class UDamageType* DamageType,
        class AController* InstigatedBy,
        AActor* DamageCauser);
		
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0"))
	float MaxHealth = 100.0f;

private:
	float Health = 0.0f;
	
};
