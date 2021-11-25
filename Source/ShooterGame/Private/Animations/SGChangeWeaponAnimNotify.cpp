// Study Shooter Game from Udemy. All Rights Reserved.


#include "Animations/SGChangeWeaponAnimNotify.h"

void USGChangeWeaponAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}
