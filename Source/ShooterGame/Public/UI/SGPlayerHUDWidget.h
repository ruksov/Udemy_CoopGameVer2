// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SGCoreTypes.h"
#include "SGPlayerHUDWidget.generated.h"

UCLASS()
class SHOOTERGAME_API USGPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual bool Initialize() override;

	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthRatio() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectating() const;

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnTakeDamage();

private:
    void OnHealthChanged(float Health, float HealthDelta);
};
