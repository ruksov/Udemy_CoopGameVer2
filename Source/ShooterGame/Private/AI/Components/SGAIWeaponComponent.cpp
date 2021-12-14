// Study Shooter Game from Udemy. All Rights Reserved.


#include "AI/Components/SGAIWeaponComponent.h"
#include "Weapon/SGBaseWeapon.h"
#include "GameFramework/Character.h"

void USGAIWeaponComponent::StartFire()
{
    if (!CanFire())
    {
        return;
    }
    if (CurrentWeapon->IsAmmoEmpty())
    {
        NextWeapon();
    }
    else
    {
        CurrentWeapon->StartFire();
    }
}

void USGAIWeaponComponent::OnChangeWeapon(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || Character->GetMesh() != MeshComponent || !CanEquip())
    {
        return;
    }

    int NextWeaponIndex = (CurrenWeaponIndex + 1) % Weapons.Num();
    while (NextWeaponIndex != CurrenWeaponIndex && Weapons[NextWeaponIndex]->IsAmmoEmpty())
    {
        NextWeaponIndex = (CurrenWeaponIndex + 1) % Weapons.Num();
    }

    if (NextWeaponIndex != CurrenWeaponIndex)
    {
        CurrenWeaponIndex = NextWeaponIndex;
        EquipWeapon(CurrenWeaponIndex);
    }
}
