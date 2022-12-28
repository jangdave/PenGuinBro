// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBomb.h"
#include "Components/BoxComponent.h"
#include "Components/MeshComponent.h"
#include "BombRange.h"
#include "EnemyDinosaur.h"

// Sets default values
APlayerBomb::APlayerBomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(boxComp);
	
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerBomb::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerBomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//����� �ð��� ����
	currentTime += DeltaTime;

	if (currentTime > explosionTime)
	{
		GetWorld()->SpawnActor<ABombRange>(bombRange, GetActorTransform());
		
		Destroy();

		//������ �ð��� �ٽ� 0���� �ʱ�ȭ
		currentTime = 0;
	}
	
}
