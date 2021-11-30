// Study Shooter Game from Udemy. All Rights Reserved.


#include "Components/SGWeaponComponent.h"
#include "Weapon/SGBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/SGEquipFinishedAnimNotify.h"
#include "Animations/SGChangeWeaponAnimNotify.h"
#include "Animations/SGReloadFinishedAnimNotify.h"

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

    StopFire();

    EquipAnimInProgress = true;
    PlayAnimMontage(EquipAnimMontage);
}

void USGWeaponComponent::Reload()
{
    StopFire();
    ChangeClip();
}

void USGWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    checkf(WeaponDatas.Num() == 2, TEXT("Our character can hold only 2 weapons items"))

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

    for (FWeaponData& WeaponData : WeaponDatas)
    {
        ASGBaseWeapon* Weapon = World->SpawnActor<ASGBaseWeapon>(WeaponData.WeaponClass);
        if (!Weapon)
        {
            continue;
        }

        Weapon->OnClipEmpty.AddUObject(this, &USGWeaponComponent::OnClipEmpty);
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
    if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
    {
        return;
    }

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character)
    {
        return;
    }

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }

    CurrentWeapon = Weapons[WeaponIndex];

    const FWeaponData* CurrentWeaponData = WeaponDatas.FindByPredicate(
        [WeaponToSearch = CurrentWeapon](const FWeaponData& WeaponData)
        {
            return WeaponToSearch->GetClass() == WeaponData.WeaponClass;
        });

    CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
}

void USGWeaponComponent::InitAnimations()
{
    if (!EquipAnimMontage)
    {
        return;
    }

    bool isAllAnimNotifiesSet = true;

    isAllAnimNotifiesSet |= AddCallbackToAnimNotifyByClass<USGEquipFinishedAnimNotify>(EquipAnimMontage, this, &USGWeaponComponent::OnEqiupFinished);
    isAllAnimNotifiesSet |= AddCallbackToAnimNotifyByClass<USGChangeWeaponAnimNotify>(EquipAnimMontage, this, &USGWeaponComponent::OnChangeWeapon);

    for (FWeaponData& WeaponData : WeaponDatas)
    {
        isAllAnimNotifiesSet |= AddCallbackToAnimNotifyByClass<USGReloadFinishedAnimNotify>(WeaponData.ReloadAnimMontage, this, &USGWeaponComponent::OnReloadFinished);
    }

    checkf(isAllAnimNotifiesSet, TEXT("Some of animation notifies falied to set!"));
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

void USGWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || Character->GetMesh() != MeshComponent)
    {
        return;
    }

    ReloadAnimInProgress = false;
}

bool USGWeaponComponent::CanFire() const
{
    return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool USGWeaponComponent::CanEquip() const
{
    return !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool USGWeaponComponent::CanReload() const
{
    return CurrentWeapon && CurrentWeapon->CanReload() && !EquipAnimInProgress && !ReloadAnimInProgress;
}

void USGWeaponComponent::OnClipEmpty()
{
    ChangeClip();
}

void USGWeaponComponent::ChangeClip()
{
    if (!CanReload())
    {
        return;
    }

    CurrentWeapon->ChangeClip();

    ReloadAnimInProgress = true;
    PlayAnimMontage(CurrentReloadAnimMontage);
}

