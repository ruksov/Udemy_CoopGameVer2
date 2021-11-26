// Study Shooter Game from Udemy. All Rights Reserved.


#include "Animations/SGBaseAnimNotify.h"

void USGBaseAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}