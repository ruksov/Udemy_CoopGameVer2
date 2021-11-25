// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SGEquipFinishedAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, USkeletalMeshComponent*)

/**
 *
 */
UCLASS()
class SHOOTERGAME_API USGEquipFinishedAnimNotify : public UAnimNotify
{
    GENERATED_BODY()

public:
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
    FOnNotifiedSignature OnNotified;
};
