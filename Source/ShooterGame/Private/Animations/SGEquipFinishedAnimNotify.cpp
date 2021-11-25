// Study Shooter Game from Udemy. All Rights Reserved.


#include "Animations/SGEquipFinishedAnimNotify.h"

void USGEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}
