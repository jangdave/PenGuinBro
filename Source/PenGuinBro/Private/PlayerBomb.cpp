// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBomb.h"
#include "Components/BoxComponent.h"
#include "Components/MeshComponent.h"
#include "BombRange.h"
#include "EnemyDinosaur.h"
#include "Kismet/Gameplaystatics.h"

// Sets default values
APlayerBomb::APlayerBomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(boxComp);
	boxComp->SetCollisionProfileName(TEXT("BombPreset"));
	
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetCollisionProfileName(TEXT("BombMeshPreset"));
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
		//FActorSpawnParameters param;
		//param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<ABombRange>(bombRange, GetActorTransform());
		
		Destroy();

		UGameplayStatics::PlaySound2D(this, fireSound);

		//������ �ð��� �ٽ� 0���� �ʱ�ȭ
		currentTime = 0;
	}
	
}
