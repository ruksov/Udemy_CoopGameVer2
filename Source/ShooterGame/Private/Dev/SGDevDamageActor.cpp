// Study Shooter Game from Udemy. All Rights Reserved.


#include "Dev/SGDevDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASGDevDamageActor::ASGDevDamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
}

// Called when the game starts or when spawned
void ASGDevDamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASGDevDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), SphereRadius, 24, SphereColor);
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), SphereRadius, DamageType, {}, this, nullptr, DoFullDamage);
}

