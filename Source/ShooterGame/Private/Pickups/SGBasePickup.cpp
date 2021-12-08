// Study Shooter Game from Udemy. All Rights Reserved.


#include "Pickups/SGBasePickup.h"
#include "Components/SphereComponent.h"

// Sets default values
ASGBasePickup::ASGBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(InitCollisionRadius);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);
}

void ASGBasePickup::BeginPlay()
{
	Super::BeginPlay();
	
    check(CollisionComponent);
 
    GenerateRotationPeriod();
}

void ASGBasePickup::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    Rotate(DeltaSeconds);
}

void ASGBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    APawn* Pawn = Cast<APawn>(OtherActor);
    if (ApplyPickupTo(Pawn))
    {
        PickupWasTaken();
    }
}

bool ASGBasePickup::ApplyPickupTo(APawn* Pawn)
{
    return false;
}

void ASGBasePickup::PickupWasTaken()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    GetRootComponent()->SetVisibility(false, true);

    FTimerHandle RespawnTimerHandle;
    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASGBasePickup::Respawn, RespawnTime);
}

void ASGBasePickup::Respawn()
{
    GenerateRotationPeriod();
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    GetRootComponent()->SetVisibility(true, true);
}

void ASGBasePickup::GenerateRotationPeriod()
{
    RotationPeriodInSec = FMath::RandRange(RotationPeriodMinInSec, RotationPeriodMaxInSec);
    RotationPeriodInSec *= FMath::RandBool() ? 1.0 : -1.0f;
}

void ASGBasePickup::Rotate(float DeltaSeconds)
{
    AddActorWorldRotation(FRotator(0.0f, (DeltaSeconds / RotationPeriodInSec) * 360.0f, 0.0f));
}
