// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SGHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)

USTRUCT(BlueprintType)
struct FAutoHealInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool IsEnabled = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "IsEnabled"))
    float StartDelay = 3.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "IsEnabled"))
    float UpdateTime = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "IsEnabled"))
    float UpdateValue = 1.0f;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAME_API USGHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USGHealthComponent();

    UFUNCTION(BlueprintCallable)
    bool IsDead() const { return Health <= 0.0f; }

	float GetHealth() const { return Health; }
    float GetMaxHealth() const { return MaxHealth; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetHealth(float NewHealth);

private:
    UFUNCTION()
    void OnTakeAnyDamage(
        AActor* DamagedActor,
        float Damage,
        const class UDamageType* DamageType,
        class AController* InstigatedBy,
        AActor* DamageCauser);

    void AutoHealUpdate();
    void UpdateAutoHealTimer(bool needActivate);

public:
    FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0"))
    float MaxHealth = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
    FAutoHealInfo AutoHealInfo;

private:
	float Health = 0.0f;
    FTimerHandle AutoHealTimerHandle;
};
