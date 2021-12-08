// Study Shooter Game from Udemy. All Rights Reserved.


#include "Components/SGHealthComponent.h"
#include "Camera/CameraShakeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

USGHealthComponent::USGHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


bool USGHealthComponent::TryAddHealth(float HealthToAdd)
{
    if (IsDead() || IsHealthFull())
    {
        return false;
    }

    SetHealth(Health + HealthToAdd);
    return true;
}

// Called when the game starts
void USGHealthComponent::BeginPlay()
{
	Super::BeginPlay();

    check(MaxHealth > 0.0f);
	
	SetHealth(MaxHealth);

    if (AActor* ComponentOwner = GetOwner())
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USGHealthComponent::OnTakeAnyDamage);
    }
}

void USGHealthComponent::SetHealth(float NewHealth)
{
    const float NewHealthClamped = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    const float HealthDelta = NewHealthClamped - Health;

    Health = NewHealthClamped;
    OnHealthChanged.Broadcast(Health, HealthDelta);
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
    UpdateAutoHealTimer(true);

    if (IsDead())
    {
        OnDeath.Broadcast();
        UpdateAutoHealTimer(false);
    }

    PlayCameraShake();
}

void USGHealthComponent::AutoHealUpdate()
{
    if (IsHealthFull())
    {
        UpdateAutoHealTimer(false);
    }
    else
    {
        SetHealth(Health + AutoHealInfo.UpdateValue);
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

bool USGHealthComponent::IsHealthFull() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}

void USGHealthComponent::PlayCameraShake()
{
    if (IsDead())
    {
        return;
    }

    const APawn* Pawn = Cast<APawn>(GetOwner());
    const APlayerController* Controller = Pawn ? Pawn->GetController<APlayerController>() : nullptr;
    if (!Controller || !Controller->PlayerCameraManager)
    {
        return;
    }

    Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}
