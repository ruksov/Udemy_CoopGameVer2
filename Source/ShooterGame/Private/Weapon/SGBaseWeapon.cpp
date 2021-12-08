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

void ASGBaseWeapon::ChangeClip()
{
    if (!CurrentAmmo.Infinite)
    {
        if (CurrentAmmo.Clips == 0)
        {
            UE_LOG(LogBaseWeapon, Warning, TEXT("No more clips!"));
            return;
        }

        --CurrentAmmo.Clips;
    }

    CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    UE_LOG(LogBaseWeapon, Display, TEXT("----- Change Clip -----"));
}

bool ASGBaseWeapon::CanReload()
{
    return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

bool ASGBaseWeapon::TryAddAmmo(int32 ClipsAmount)
{
    if (CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <= 0)
    {
        return false;
    }

    const int32 NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
    CurrentAmmo.Clips = FMath::Clamp(NextClipsAmount, 0, DefaultAmmo.Clips);
    
    if (NextClipsAmount > DefaultAmmo.Clips && CurrentAmmo.Bullets < DefaultAmmo.Bullets)
    {
        // Make reload logic.
        StopFire();
        ++CurrentAmmo.Clips;
        OnClipEmpty.Broadcast(this);
    }

    return true;
}

void ASGBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	check(WeaponMesh);
    CurrentAmmo = DefaultAmmo;
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
        CollisionParams.bReturnPhysicalMaterial = true;

        World->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
	}

	return HitResult;
}

void ASGBaseWeapon::DecreaseAmmo()
{
    if (CurrentAmmo.Bullets == 0)
    {
        UE_LOG(LogBaseWeapon, Warning, TEXT("Clip is empty!"));
        return;
    }

    --CurrentAmmo.Bullets;

    if (IsClipEmpty() && !IsAmmoEmpty())
    {
        StopFire();
        OnClipEmpty.Broadcast(this);
    }
}

bool ASGBaseWeapon::IsAmmoEmpty() const
{
    return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool ASGBaseWeapon::IsClipEmpty() const
{
    return CurrentAmmo.Bullets == 0;
}

bool ASGBaseWeapon::IsAmmoFull() const
{
    return CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

void ASGBaseWeapon::LogAmmo()
{
    FString const AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / "
        + (CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips));

    UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo);
}
