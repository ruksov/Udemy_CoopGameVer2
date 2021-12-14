// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SGWeaponComponent.h"
#include "SGAIWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API USGAIWeaponComponent : public USGWeaponComponent
{
	GENERATED_BODY()
	
public:
    virtual void StartFire() override;

protected:
    virtual void OnChangeWeapon(USkeletalMeshComponent* MeshComponent) override;
};
