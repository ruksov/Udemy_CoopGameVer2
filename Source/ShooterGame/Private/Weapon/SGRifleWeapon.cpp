// Study Shooter Game from Udemy. All Rights Reserved.


#include "Weapon/SGRifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/SGWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ASGRifleWeapon::ASGRifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<USGWeaponFXComponent>("WeaponFXComponent");
}

void ASGRifleWeapon::StartFire()
{
    InitMuzzleFX();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASGRifleWeapon::Fire, TimeBetwenShots, true, 0.0f);
}

void ASGRifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    SetMuzzleFXVisibility(false);
}

void ASGRifleWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponFXComponent);
}

void ASGRifleWeapon::Fire()
{
    UWorld* World = GetWorld();
    if (!World || IsAmmoEmpty())
    {
        StopFire();
        return;
    }

    FVector TraceStart;
    FVector TraceEnd;
    if (!GetShootTraceData(TraceStart, TraceEnd))
    {
        StopFire();
        return;
    }

    FHitResult const HitResult = MakeShot(TraceStart, TraceEnd);

    FVector TraceFXEnd = TraceEnd;
    if (IsShotHitSomething(HitResult))
    {
        TraceFXEnd = HitResult.ImpactPoint;
        HandleHitActor(HitResult);
        WeaponFXComponent->PlayImpactFX(HitResult);
    }

    SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);
    DecreaseAmmo();
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

void ASGRifleWeapon::InitMuzzleFX()
{
    if (!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }
    SetMuzzleFXVisibility(true);
}

void ASGRifleWeapon::SetMuzzleFXVisibility(bool Visible)
{
    if (MuzzleFXComponent)
    {
        MuzzleFXComponent->SetPaused(!Visible);
        MuzzleFXComponent->SetVisibility(Visible, true);
    }
}

void ASGRifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
    if (UNiagaraComponent* TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart))
    {
        TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
    }
}
