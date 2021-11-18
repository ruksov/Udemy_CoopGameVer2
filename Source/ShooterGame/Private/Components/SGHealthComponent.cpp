// Study Shooter Game from Udemy. All Rights Reserved.


#include "Components/SGHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

USGHealthComponent::USGHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void USGHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	SetHealth(MaxHealth);

    if (AActor* ComponentOwner = GetOwner())
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USGHealthComponent::OnTakeAnyDamage);
    }
}

void USGHealthComponent::SetHealth(float NewHealth)
{
    if (NewHealth < Health)
    {
        UpdateAutoHealTimer(true);
    }

    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}

void USGHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor,
    float Damage,
    const class UDamageType* DamageType,
    class AController* InstigatedBy,
    AActor* DamageCauser)
{
    if (IsDead())
    {
        return;
    }

    SetHealth(Health - Damage);

    if (IsDead())
    {
        OnDeath.Broadcast();
        UpdateAutoHealTimer(false);
    }
}

void USGHealthComponent::AutoHealUpdate()
{
    if (Health < MaxHealth)
    {
        SetHealth(Health + AutoHealInfo.UpdateValue);
    }
    else
    {
        UpdateAutoHealTimer(false);
    }
}

void USGHealthComponent::UpdateAutoHealTimer(bool needActivate)
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    if (needActivate && AutoHealInfo.IsEnabled)
    {
        World->GetTimerManager().SetTimer(AutoHealTimerHandle,
            this,
            &USGHealthComponent::AutoHealUpdate,
            AutoHealInfo.UpdateTime,
            true,
            AutoHealInfo.StartDelay);
    }
    else
    {
        World->GetTimerManager().ClearTimer(AutoHealTimerHandle);
    }
}
