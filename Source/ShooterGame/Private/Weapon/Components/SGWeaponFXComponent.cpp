// Study Shooter Game from Udemy. All Rights Reserved.


#include "Weapon/Components/SGWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"

USGWeaponFXComponent::USGWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void USGWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	FImpactData ImpactData = DefaultImpactData;

	if (UPhysicalMaterial* HitPhysMaterial = Hit.PhysMaterial.Get())
	{
		if (ImpactDataMap.Contains(HitPhysMaterial))
		{
			ImpactData = ImpactDataMap[HitPhysMaterial];
		}
	}

	// Spawn Niagar effect
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactData.Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());

	// Spawn Decal
	FDecalData const& DecalData = ImpactData.DecalData;
	UDecalComponent* DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), 
		DecalData.Material, 
		DecalData.Size, 
		Hit.ImpactPoint, 
		Hit.ImpactNormal.Rotation());

	if (DecalComponent)
	{
		DecalComponent->SetFadeOut(DecalData.LifeTime, DecalData.FadeOutTime);
	}
}

