// Study Shooter Game from Udemy. All Rights Reserved.


#include "UI/SGPlayerHUDWidget.h"
#include "Components/SGHealthComponent.h"
#include "Components/SGWeaponComponent.h"
#include "SGUtils.h"

float USGPlayerHUDWidget::GetHealthRatio() const
{
    const USGHealthComponent* HealthComponent = SGUtils::GetPlayerComponentByClass<USGHealthComponent>(GetOwningPlayerPawn());
    return HealthComponent ? HealthComponent->GetHealthRatio() : 0.0f;
}

bool USGPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    const USGWeaponComponent* WeaponComponent = SGUtils::GetPlayerComponentByClass<USGWeaponComponent>(GetOwningPlayerPawn());
    return WeaponComponent ? WeaponComponent->GetCurrentWeaponUIData(UIData) : false;
}

bool USGPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
    const USGWeaponComponent* WeaponComponent = SGUtils::GetPlayerComponentByClass<USGWeaponComponent>(GetOwningPlayerPawn());
    return WeaponComponent ? WeaponComponent->GetCurrentWeaponAmmoData(AmmoData) : false;
}

bool USGPlayerHUDWidget::IsPlayerAlive() const
{
    const USGHealthComponent* HealthComponent = SGUtils::GetPlayerComponentByClass<USGHealthComponent>(GetOwningPlayerPawn());
    return HealthComponent && !HealthComponent->IsDead();
}

bool USGPlayerHUDWidget::IsPlayerSpectating() const
{
    const APlayerController* Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}
