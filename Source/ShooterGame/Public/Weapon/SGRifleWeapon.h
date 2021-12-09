// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SGBaseWeapon.h"
#include "SGRifleWeapon.generated.h"

class USGWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class SHOOTERGAME_API ASGRifleWeapon : public ASGBaseWeapon
{
	GENERATED_BODY()
	
public:
    ASGRifleWeapon();

    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    virtual void BeginPlay() override;
    virtual void Fire() override;
    virtual bool GetShootTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

    bool IsShotHitSomething(const FHitResult& HitResult) const;
    void HandleHitActor(const FHitResult& HitResult);

private:
    void InitMuzzleFX();
    void SetMuzzleFXVisibility(bool Visible);
    void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);

protected:
    UPROPERTY(VisibleAnywhere, Category = "VFX")
    USGWeaponFXComponent* WeaponFXComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* TraceFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FString TraceTargetName = "TraceTarget";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TimeBetwenShots = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float BulletSpreadAngle = 3.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount = 10.0f;

private:
    FTimerHandle ShotTimerHandle;

    UPROPERTY()
    UNiagaraComponent* MuzzleFXComponent;
};
