// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SGGameHUD.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API ASGGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;

protected:
	virtual void BeginPlay() override;

private:
	void DrawCrossHair();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
};
