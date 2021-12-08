// Study Shooter Game from Udemy. All Rights Reserved.


#include "Weapon/SGProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/SGWeaponFXComponent.h"

ASGProjectile::ASGProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
    CollisionComponent->InitSphereRadius(InitCollisionRadius);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Block);
    CollisionComponent->bReturnMaterialOnMove = true;
    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
    MovementComponent->InitialSpeed = 2000.0f;
    MovementComponent->ProjectileGravityScale = 0.0f;

    WeaponFXComponent = CreateDefaultSubobject<USGWeaponFXComponent>("WeaponFXComponent");
}

void ASGProjectile::BeginPlay()
{
    Super::BeginPlay();

    check(CollisionComponent);
    check(MovementComponent);
    check(WeaponFXComponent);

    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
    CollisionComponent->OnComponentHit.AddDynamic(this, &ASGProjectile::OnProjectileHit);
    SetLifeSpan(LifeSeconds);
}

void ASGProjectile::OnProjectileHit(
    UPrimitiveComponent* HitComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    FVector NormalImpulse,
    const FHitResult& Hit)
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    MovementComponent->StopMovementImmediately();

    UGameplayStatics::ApplyRadialDamage(World,
        DamageAmount,
        GetActorLocation(),
        DamageRadius,
        UDamageType::StaticClass(),
        { GetOwner() },
        this,
        GetController(),
        DoFullDamage);

    DrawDebugSphere(World, GetActorLocation(), DamageRadius, 24, FColor::Red, false, 5.0f);

    WeaponFXComponent->PlayImpactFX(Hit);

    Destroy();
}

AController* ASGProjectile::GetController() const
{
    const APawn* Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}

