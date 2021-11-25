// Study Shooter Game from Udemy. All Rights Reserved.


#include "Components/SGWeaponComponent.h"
#include "Weapon/SGBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/SGEquipFinishedAnimNotify.h"
#include "Animations/SGChangeWeaponAnimNotify.h"

USGWeaponComponent::USGWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USGWeaponComponent::StartFire()
{
    if (!CanFire())
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
    if (!CanEquip())
    {
        return;
    }

    EquipAnimInProgress = true;
    PlayAnimMontage(EquipAnimMontage);
}

void USGWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    CurrenWeaponIndex = 0;
    SpawnWeapons();
    EquipWeapon(CurrenWeaponIndex);
    InitAnimations();
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

void USGWeaponComponent::InitAnimations()
{
    if (!EquipAnimMontage)
    {
        return;
    }

    TArray<FAnimNotifyEvent>& NotifyEvents = EquipAnimMontage->Notifies;
    for (FAnimNotifyEvent& NotifyEvent : NotifyEvents)
    {
        if (auto EquipFinishNotify = Cast<USGEquipFinishedAnimNotify>(NotifyEvent.Notify))
        {
            EquipFinishNotify->OnNotified.AddUObject(this, &USGWeaponComponent::OnEqiupFinished);
        }
        else if (auto ChangeWeaponNotify = Cast<USGChangeWeaponAnimNotify>(NotifyEvent.Notify))
        {
            ChangeWeaponNotify->OnNotified.AddUObject(this, &USGWeaponComponent::OnChangeWeapon);
        }
    }
}

void USGWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character)
    {
        return;
    }

    Character->PlayAnimMontage(Animation);
}

void USGWeaponComponent::OnEqiupFinished(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || Character->GetMesh() != MeshComponent)
    {
        return;
    }

    EquipAnimInProgress = false;
}

void USGWeaponComponent::OnChangeWeapon(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || Character->GetMesh() != MeshComponent)
    {
        return;
    }

    CurrenWeaponIndex = (CurrenWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrenWeaponIndex);
}

bool USGWeaponComponent::CanFire() const
{
    return CurrentWeapon && !EquipAnimInProgress;
}

bool USGWeaponComponent::CanEquip() const
{
    return !EquipAnimInProgress;
}

