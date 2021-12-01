// Study Shooter Game from Udemy. All Rights Reserved.


#include "Pickups/SGBasePickup.h"
#include "Components/SphereComponent.h"

// Sets default values
ASGBasePickup::ASGBasePickup()
{
	PrimaryActorTick.bCanEverTick = false;

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
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    GetRootComponent()->SetVisibility(true, true);
}
