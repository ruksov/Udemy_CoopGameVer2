// Study Shooter Game from Udemy. All Rights Reserved.


#include "SGGameModeBase.h"
#include "Player/SGBaseCharacter.h"
#include "Player/SGPlayerController.h"

ASGGameModeBase::ASGGameModeBase()
{
    DefaultPawnClass = ASGBaseCharacter::StaticClass();
    PlayerControllerClass = ASGPlayerController::StaticClass();
}