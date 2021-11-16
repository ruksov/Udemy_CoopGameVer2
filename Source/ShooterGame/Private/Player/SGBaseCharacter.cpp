// Study Shooter Game from Udemy. All Rights Reserved.


#include "Player/SGBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SGCharacterMovementComponent.h"

// Sets default values
ASGBaseCharacter::ASGBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USGCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ASGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

bool ASGBaseCharacter::IsRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

float ASGBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero())
    {
        return 0.0f;
    }

    const FVector VelocityNormal = GetVelocity().GetSafeNormal();
    const float AngleBetween = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal)));
    const FVector CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    return CrossProduct.IsZero() ? AngleBetween : AngleBetween * FMath::Sign(CrossProduct.Z);
}

// Called every frame
void ASGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASGBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!PlayerInputComponent)
	{
        return;
	}

	PlayerInputComponent->BindAxis("MoveForward", this, &ASGBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASGBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ASGBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ASGBaseCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ASGBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ASGBaseCharacter::StartRun);
    PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ASGBaseCharacter::StopRun);
}

void ASGBaseCharacter::MoveForward(float Amount)
{
    IsMovingForward = Amount > 0;

    if (!FMath::IsNearlyZero(Amount))
    {
        AddMovementInput(GetActorForwardVector(), Amount);
    }
}

void ASGBaseCharacter::MoveRight(float Amount)
{
    if (!FMath::IsNearlyZero(Amount))
    {
        AddMovementInput(GetActorRightVector(), Amount);
    }
}

void ASGBaseCharacter::StartRun()
{
    WantsToRun = true;
}

void ASGBaseCharacter::StopRun()
{
    WantsToRun = false;
}