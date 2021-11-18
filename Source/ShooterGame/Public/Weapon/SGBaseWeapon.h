// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SHOOTERGAME_API ASGBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASGBaseWeapon();

	virtual void Fire();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

};
