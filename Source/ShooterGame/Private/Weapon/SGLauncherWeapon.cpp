// Study Shooter Game from Udemy. All Rights Reserved.


#include "Weapon/SGLauncherWeapon.h"
#include "Weapon/SGProjectile.h"

void ASGLauncherWeapon::StartFire()
{
    Fire();
}

void ASGLauncherWeapon::Fire()
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

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    ASGProjectile* Projectile = World->SpawnActorDeferred<ASGProjectile>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }
}
