// Study Shooter Game from Udemy. All Rights Reserved.


#include "Components/SGWeaponComponent.h"
#include "Weapon/SGBaseWeapon.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
USGWeaponComponent::USGWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USGWeaponComponent::StartFire()
{
    if (!CurrentWeapon)
    {
        return;
    }

    CurrentWeapon->StartFire();
}

void USGWeaponComponent::StopFire()
{
    if (!CurrentWeapon)
    {
        return;
    }

    CurrentWeapon->StopFire();
}

void USGWeaponComponent::NextWeapon()
{
    CurrenWeaponIndex = (CurrenWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrenWeaponIndex);
}

void USGWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
    CurrenWeaponIndex = 0;
    SpawnWeapons();
    EquipWeapon(CurrenWeaponIndex);
}

void USGWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;
    for (ASGBaseWeapon* Weapon : Weapons)
    {
        Weapon->StopFire();
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();

    Super::EndPlay(EndPlayReason);
}

void USGWeaponComponent::SpawnWeapons()
{
    UWorld* World = GetWorld();
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!World || !Character)
    {
        return;
    }

    for (TSubclassOf<ASGBaseWeapon> WeaponClass : WeaponClasses)
    {
        ASGBaseWeapon* Weapon = World->SpawnActor<ASGBaseWeapon>(WeaponClass);
        if (!Weapon)
        {
            continue;
        }

        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);

        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
    }
}

void USGWeaponComponent::AttachWeaponToSocket(ASGBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
    if (!Weapon || !SceneComponent)
    {
        return;
    }

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void USGWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || WeaponIndex >= Weapons.Num())
    {
        return;
    }

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }

    CurrentWeapon = Weapons[WeaponIndex];
    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
}

