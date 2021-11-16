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

void USGHealthComponent::SetHealth(float Value)
{
    Health = Value;
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

    SetHealth(FMath::Clamp(Health - Damage, 0.0f, MaxHealth));

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
}