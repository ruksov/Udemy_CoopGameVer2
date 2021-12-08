// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SGHealthComponent.generated.h"

class UCameraShakeBase;

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, float)

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

    UFUNCTION(BlueprintCallable, Category = "Health")
    bool IsDead() const { return Health <= 0.0f; }

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealthRatio() const { return Health / MaxHealth; }

	float GetHealth() const { return Health; }
    float GetMaxHealth() const { return MaxHealth; }

    bool TryAddHealth(float HealthToAdd);

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

    bool IsHealthFull() const;

    void PlayCameraShake();

public:
    FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0"))
    float MaxHealth = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
    FAutoHealInfo AutoHealInfo;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TSubclassOf<UCameraShakeBase> CameraShake;

private:
	float Health = 0.0f;
    FTimerHandle AutoHealTimerHandle;
};
