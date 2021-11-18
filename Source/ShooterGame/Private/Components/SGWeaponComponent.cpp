// Study Shooter Game from Udemy. All Rights Reserved.


#include "Components/SGWeaponComponent.h"
#include "Weapon/SGBaseWeapon.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
USGWeaponComponent::USGWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void USGWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
    SpawnWeapon();
}

void USGWeaponComponent::Fire()
{
    if (!CurrentWeapon)
    {
        return;
    }

    CurrentWeapon->Fire();
}

void USGWeaponComponent::SpawnWeapon()
{
    UWorld* World = GetWorld();
    const ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!World || !Character)
    {
        return;
    }

    CurrentWeapon = World->SpawnActor<ASGBaseWeapon>(WeaponClass);
    if (!CurrentWeapon)
    {
        return;
    }

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
}

