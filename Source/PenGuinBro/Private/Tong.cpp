// Fill out your copyright notice in the Description page of Project Settings.


#include "Tong.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATong::ATong()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(15.0f, 15.0f, 25.0f));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATong::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATong::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

