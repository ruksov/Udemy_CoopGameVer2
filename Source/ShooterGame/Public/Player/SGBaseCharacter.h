// Study Shooter Game from Udemy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SGBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USGHealthComponent;
class UTextRenderComponent;

UCLASS()
class SHOOTERGAME_API ASGBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASGBaseCharacter(const FObjectInitializer& ObjInit);

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsRunning() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USGHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent* HealthTextComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* DeathAnimMontage;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    void MoveForward(float Amount);
    void MoveRight(float Amount);

	void StartRun();
    void StopRun();

    void OnDeath();
    void OnHealthChanged(float Health);

private:
	bool WantsToRun = false;
	bool IsMovingForward = false;
};
