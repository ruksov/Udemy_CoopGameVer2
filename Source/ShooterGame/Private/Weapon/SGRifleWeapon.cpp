// Study Shooter Game from Udemy. All Rights Reserved.


#include "Weapon/SGRifleWeapon.h"
#include "DrawDebugHelpers.h"

void ASGRifleWeapon::StartFire()
{
    Fire();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASGRifleWeapon::Fire, TimeBetwenShots, true);
}

void ASGRifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ASGRifleWeapon::Fire()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    FVector TraceStart;
    FVector TraceEnd;
    if (!GetShootTraceData(TraceStart, TraceEnd))
    {
        return;
    }

    FHitResult const HitResult = MakeShot(TraceStart, TraceEnd);

    if (IsShotHitSomething(HitResult))
    {
        DrawDebugLine(World, GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
        DrawDebugSphere(World, HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
        HandleHitActor(HitResult);
    }
    else
    {
        DrawDebugLine(World, GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
    }
}

bool ASGRifleWeapon::GetShootTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
    {
        return false;
    }

    TraceStart = ViewLocation;
    const float HalfBulletSpreadAngleRad = FMath::DegreesToRadians(BulletSpreadAngle / 2);
    const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfBulletSpreadAngleRad);
    TraceEnd = TraceStart + ShootDirection * ShootMaxDistance;
    return true;
}

bool ASGRifleWeapon::IsShotHitSomething(const FHitResult& HitResult) const
{
    if (!HitResult.bBlockingHit)
    {
        return false;
    }

    const FVector ShootVectorFromView = HitResult.ImpactPoint - HitResult.TraceStart;
    return ShootVectorFromView.CosineAngle2D(HitResult.ImpactPoint - GetMuzzleWorldLocation()) > 0.0f;
}

void ASGRifleWeapon::HandleHitActor(const FHitResult& HitResult)
{
    AActor* HitActor = HitResult.Actor.Get();
    if (!HitActor)
    {
        return;
    }

    HitActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}
