// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SGBaseWeapon.h"
#include "SGRifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API ASGRifleWeapon : public ASGBaseWeapon
{
	GENERATED_BODY()
	
public:
    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    virtual void Fire() override;
    virtual bool GetShootTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

    bool IsShotHitSomething(const FHitResult& HitResult) const;
    void HandleHitActor(const FHitResult& HitResult);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon|Rifle")
    float TimeBetwenShots = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon|Rifle")
    float BulletSpreadAngle = 3.0f;


    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon|Rifle")
    float DamageAmount = 10.0f;

private:
    FTimerHandle ShotTimerHandle;
};