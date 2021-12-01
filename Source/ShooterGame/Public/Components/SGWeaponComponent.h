// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SGCoreTypes.h"
#include "SGWeaponComponent.generated.h"

class ASGBaseWeapon;

USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ASGBaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    UAnimMontage* ReloadAnimMontage;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTERGAME_API USGWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USGWeaponComponent();

    void StartFire();
    void StopFire();
    void NextWeapon();
    void Reload();

    bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
    bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

    bool TryAddAmmo(TSubclassOf<ASGBaseWeapon> WeaponType, int32 ClipsAmount);

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
    void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

    bool CanFire() const;
    bool CanEquip() const;
    bool CanReload() const;

    void OnClipEmpty(ASGBaseWeapon* Weapon);
    void ChangeClip();

    template<typename T>
    T* FindAnimNotifyByClass(UAnimSequenceBase* Animation)
    {
        if (Animation)
        {
            TArray<FAnimNotifyEvent>& NotifyEvents = Animation->Notifies;
            for (FAnimNotifyEvent& NotifyEvent : NotifyEvents)
            {
                if (auto AnimNotify = Cast<T>(NotifyEvent.Notify))
                {
                    return AnimNotify;
                }
            }
        }
        return nullptr;
    }

    template <typename NotifyClass, typename ClassType, typename FuncType>
    bool AddCallbackToAnimNotifyByClass(
        UAnimSequenceBase* Animation, 
        ClassType* ObjectPtr,
        FuncType Func)
    {
        if (NotifyClass* AnimNotify = FindAnimNotifyByClass<NotifyClass>(Animation))
        {
            AnimNotify->OnNotified.AddUObject(ObjectPtr, Func);
            return true;
        }
        return false;
    }

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<FWeaponData> WeaponDatas;

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

    UPROPERTY()
    UAnimMontage* CurrentReloadAnimMontage = nullptr;

    int32 CurrenWeaponIndex = 0;
    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;
};
