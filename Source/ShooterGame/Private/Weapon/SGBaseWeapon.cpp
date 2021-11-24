// Study Shooter Game from Udemy. All Rights Reserved.

#include "Weapon/SGBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ASGBaseWeapon::ASGBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void ASGBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	check(WeaponMesh);
}

bool ASGBaseWeapon::GetShootTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
    {
        return false;
    }

    TraceStart = ViewLocation;
    TraceEnd = TraceStart + ViewRotation.Vector() * ShootMaxDistance;
    return true;
}


APlayerController* ASGBaseWeapon::GetPlayerController() const
{
    const ACharacter* Player = Cast<ACharacter>(GetOwner());
    return Player ? Player->GetController<APlayerController>() : nullptr;
}

bool ASGBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const APlayerController* Controller = GetPlayerController();
    if (!Controller)
    {
        return false;
    }

    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	return true;
}

FVector ASGBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketTransform(MuzzleSocketName).GetLocation();
}

FHitResult ASGBaseWeapon::MakeShot(const FVector& TraceStart, const FVector& TraceEnd) const
{
	FHitResult HitResult;

	if (UWorld* World = GetWorld())
	{
        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(GetOwner());

        World->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
	}

	return HitResult;
}
