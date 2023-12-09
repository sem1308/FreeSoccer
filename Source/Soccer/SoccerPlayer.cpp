// Fill out your copyright notice in the Description page of Project Settings.


#include "SoccerPlayer.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"

ASoccerPlayer::ASoccerPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    SpringArm->SetupAttachment(RootComponent);
    Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    Camera->SetupAttachment(SpringArm);
}

void ASoccerPlayer::BeginPlay()
{
    Super::BeginPlay();

    if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
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
    }
}


void ASoccerPlayer::Move(const FInputActionValue& Value)
{
    float DeltaTime = GetWorld()->GetDeltaSeconds();

    FVector Val = Value.Get<FVector>();
    Val.Normalize();
    Val = Val * Speed * DeltaTime;    
    // UE_LOG(LogTemp, Display, TEXT("Input Value : (%f, %f)"), Val.X, Val.Y);

    FRotator Rotator(0);
    Rotator.Yaw = SpringArm->GetRelativeRotation().Yaw;

    FVector ForwardVector = UKismetMathLibrary::GetForwardVector(Rotator);
    FVector RightVector = UKismetMathLibrary::GetRightVector(Rotator);

    AddMovementInput(ForwardVector, Val.X);
    AddMovementInput(RightVector, Val.Y);
}

void ASoccerPlayer::Turn(const FInputActionValue& Value)
{
    float DeltaTime = GetWorld()->GetDeltaSeconds();

    FVector2D Val = Value.Get<FVector2D>();
    Val = Val * RotationSpeed * DeltaTime;

    UE_LOG(LogTemp, Display, TEXT("Rotation Value is (%f,%f)"), Val.X, Val.Y);

    FRotator SpringArmRotation = SpringArm->GetRelativeRotation();
    SpringArmRotation.Pitch = FMath::ClampAngle(SpringArmRotation.Pitch + Val.Y, -80.0f, 80.0f);
    SpringArmRotation.Yaw = SpringArmRotation.Yaw + Val.X;
    SpringArmRotation.Roll = 0;

    SpringArm->SetRelativeRotation(SpringArmRotation, true);

    if(USkeletalMeshComponent* PlayerMesh = GetMesh())
    {
        FRotator MeshRotation = PlayerMesh->GetRelativeRotation();
        MeshRotation.Yaw += Val.X;
        PlayerMesh->SetRelativeRotation(MeshRotation);
    }
}
