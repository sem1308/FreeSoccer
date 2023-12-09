// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHumanPawn.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ABaseHumanPawn::ABaseHumanPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ABaseHumanPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseHumanPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}