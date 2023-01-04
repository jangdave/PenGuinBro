// Fill out your copyright notice in the Description page of Project Settings.


#include "RotFloor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ARotFloor::ARotFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxCompR = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision Floor"));
	SetRootComponent(boxCompR);
	boxCompR->SetBoxExtent(FVector(62.5f, 75.0f, 12.5f));
	boxCompR->SetCollisionProfileName(TEXT("RotFloorPreset"));

	meshCompR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Floor"));
	meshCompR->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ARotFloor::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
}

// Called every frame
void ARotFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	rotSpeed = 180;

	SetActorRotation(GetActorRotation() + FRotator(0, 0, rotSpeed * DeltaTime));
}


