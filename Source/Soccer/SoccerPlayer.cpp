// Fill out your copyright notice in the Description page of Project Settings.


#include "SoccerPlayer.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ASoccerPlayer::ASoccerPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->bUsePawnControlRotation = true;
    Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    Camera->SetupAttachment(SpringArm);
}

void ASoccerPlayer::BeginPlay()
{
    Super::BeginPlay();

    if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        AddControllerPitchInput(10);
        if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(InputMappingContext,0);
        }
    }
}

// Called every frame
void ASoccerPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASoccerPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASoccerPlayer::Move);
        EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ASoccerPlayer::Turn);
        EnhancedInputComponent->BindAction(LookUpAction, ETriggerEvent::Triggered, this, &ASoccerPlayer::LookUp);
    }
}


void ASoccerPlayer::Move(const FInputActionValue& Value)
{
    FVector Val = Value.Get<FVector>();   

    AddMovementInput(GetActorForwardVector(), Val.X);
    AddMovementInput(GetActorRightVector(), Val.Y);
}

void ASoccerPlayer::Turn(const FInputActionValue& Value)
{
    float Val = Value.Get<float>();
    Val = Val * RotationSpeed * GetWorld()->GetDeltaSeconds();

    AddControllerYawInput(Val);
}

void ASoccerPlayer::LookUp(const FInputActionValue& Value)
{
    float Val = Value.Get<float>();
    Val = Val * RotationSpeed * GetWorld()->GetDeltaSeconds();

    AddControllerPitchInput(Val);
}