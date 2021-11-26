// Study Shooter Game from Udemy. All Rights Reserved.


#include "Player/SGBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Components/SGCharacterMovementComponent.h"
#include "Components/SGHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/SGWeaponComponent.h"
#include "Components/CapsuleComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

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

    HealthComponent = CreateDefaultSubobject<USGHealthComponent>("HealthComponent");
    check(HealthComponent);

    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());

    WeaponComponent = CreateDefaultSubobject<USGWeaponComponent>("WeaponComponent");
    check(WeaponComponent);
}

// Called when the game starts or when spawned
void ASGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

    check(HealthComponent);
    check(HealthTextComponent);
    check(GetCharacterMovement());

    OnHealthChanged(HealthComponent->GetHealth());

    HealthComponent->OnDeath.AddUObject(this, &ASGBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ASGBaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &ASGBaseCharacter::OnGroundLanded);
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
    check(PlayerInputComponent);
    check(WeaponComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASGBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASGBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ASGBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ASGBaseCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASGBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASGBaseCharacter::StartRun);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ASGBaseCharacter::StopRun);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USGWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USGWeaponComponent::StopFire);
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USGWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USGWeaponComponent::Reload);
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

void ASGBaseCharacter::OnDeath()
{
    PlayAnimMontage(DeathAnimMontage);
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(LifeSpanOnDeath);

    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }

    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
}

void ASGBaseCharacter::OnHealthChanged(float Health)
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void ASGBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
    const float FallVelocityZInverted = -GetVelocity().Z;
    if (FallVelocityZInverted < LandedDamageVelocityRange.X)
    {
        return;
    }

    const float FinalDamage = HealthComponent->GetMaxHealth() * FMath::GetMappedRangeValueClamped(LandedDamageVelocityRange, LandedDamageRange, FallVelocityZInverted);
    TakeDamage(FinalDamage, FDamageEvent(), nullptr, nullptr);
}
