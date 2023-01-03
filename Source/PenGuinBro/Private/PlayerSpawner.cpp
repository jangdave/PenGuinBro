// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpawner.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
APlayerSpawner::APlayerSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(sceneComp);
	arrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Comp"));
	arrowComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APlayerSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerSpawner::playerSpawn(int32 lifecount)
{
	GetWorld()->SpawnActor<APlayerPenguin>(player, arrowComp->GetComponentLocation(), arrowComp->GetComponentRotation());
}

