// Fill out your copyright notice in the Description page of Project Settings.


#include "BombRange2.h"
#include "Components/SphereComponent.h"
#include "Components/MeshComponent.h"

// Sets default values
ABombRange2::ABombRange2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp1 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SetRootComponent(sphereComp1);
}

// Called when the game starts or when spawned
void ABombRange2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABombRange2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

