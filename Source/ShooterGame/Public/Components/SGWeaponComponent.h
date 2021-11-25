// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SGWeaponComponent.generated.h"

class ASGBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTERGAME_API USGWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USGWeaponComponent();

    void StartFire();
    void StopFire();
    void NextWeapon();

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    void SpawnWeapons();
    void AttachWeaponToSocket(ASGBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
    void EquipWeapon(int32 WeaponIndex);

    void InitAnimations();
    void PlayAnimMontage(UAnimMontage* Animation);
    void OnEqiupFinished(USkeletalMeshComponent* MeshComponent);
    void OnChangeWeapon(USkeletalMeshComponent* MeshComponent);

    bool CanFire() const;
    bool CanEquip() const;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<TSubclassOf<ASGBaseWeapon>> WeaponClasses;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* EquipAnimMontage;

private:
    UPROPERTY()
    ASGBaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<ASGBaseWeapon*> Weapons;

    int32 CurrenWeaponIndex = 0;
    bool EquipAnimInProgress = false;
};
