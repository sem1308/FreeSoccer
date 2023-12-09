// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseHumanPawn.generated.h"

UCLASS()
class SOCCER_API ABaseHumanPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseHumanPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	USkeletalMeshComponent* GetMesh() const {return Mesh;}

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Component")
	class USkeletalMeshComponent* Mesh;
};
