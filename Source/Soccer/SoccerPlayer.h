// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseHumanPawn.h"
#include "InputActionValue.h"
#include "SoccerPlayer.generated.h"

class UInputMappingContext;
class UInputAction;

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class SOCCER_API ASoccerPlayer : public ABaseHumanPawn
{
	GENERATED_BODY()

public:	
	ASoccerPlayer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void BeginPlay();

private:
	//== Component ==//
	UPROPERTY(EditDefaultsOnly, Category="Component")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, Category="Component")
	UCameraComponent* Camera;

	//== Input ==//
	UPROPERTY(EditAnywhere, Category="Input")
	UInputMappingContext* InputMappingContext;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* TurnAction;

	UPROPERTY(EditAnywhere, Category="Status")
	float Speed = 500.f;

	UPROPERTY(EditAnywhere, Category="Status")
	float RotationSpeed = 120.f;

	void Move(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
};
