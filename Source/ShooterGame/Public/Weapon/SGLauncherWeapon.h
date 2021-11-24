// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SGBaseWeapon.h"
#include "SGLauncherWeapon.generated.h"

class ASGProjectile;

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API ASGLauncherWeapon : public ASGBaseWeapon
{
	GENERATED_BODY()
	
public:
	virtual void StartFire() override;

protected:
	virtual void Fire() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ASGProjectile> ProjectileClass;
};
