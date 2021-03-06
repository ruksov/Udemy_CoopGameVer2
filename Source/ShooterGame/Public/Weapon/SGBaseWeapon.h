// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGCoreTypes.h"
#include "SGBaseWeapon.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, ASGBaseWeapon*);

class USkeletalMeshComponent;
class APlayerController;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class SHOOTERGAME_API ASGBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASGBaseWeapon();

	virtual void StartFire() {}
	virtual void StopFire() {}

    void ChangeClip();
	bool CanReload();

	FWeaponUIData const& GetUIData() const { return UIData; }
	FAmmoData const& GetAmmoData() const { return CurrentAmmo; }

    bool TryAddAmmo(int32 ClipsAmount);
    bool IsAmmoEmpty() const;

protected:
	virtual void BeginPlay() override;

	virtual void Fire() {}
    virtual bool GetShootTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	APlayerController* GetPlayerController() const;
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	FVector GetMuzzleWorldLocation() const;
	FHitResult MakeShot(const FVector& TraceStart, const FVector& TraceEnd) const;

	void DecreaseAmmo();
	bool IsClipEmpty() const;
	bool IsAmmoFull() const;
	void LogAmmo();

	UNiagaraComponent* SpawnMuzzleFX() const;

public:
	FOnClipEmptySignature OnClipEmpty;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float ShootMaxDistance = 1500;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoData DefaultAmmo { 15, 10, false };

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FWeaponUIData UIData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* MuzzleFX;

private:
	FAmmoData CurrentAmmo;
};
