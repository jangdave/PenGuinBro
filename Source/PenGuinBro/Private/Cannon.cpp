// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerBomb.h"
#include "Components/ArrowComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(boxComp);
	boxComp->SetCollisionProfileName(TEXT("CannonPreset"));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);

	shootArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Shoot Arrow"));
	shootArrow->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ACannon::CannonShoot);
}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//isShootReady가 참이면
	if (isShootReady) {
		//슛 애로우 위치와 방향으로 playerbomb을 생성하고
		GetWorld()->SpawnActor<APlayerBomb>(bombFactory, shootArrow->GetComponentLocation(), shootArrow->GetComponentRotation());
		//isShootReady를 거짓으로 바꿈

		//1초 후 대포의 포신이 내려감
		//FTimerHandle cannonRot;
		//GetWorld()->GetTimerManager().SetTimer(cannonRot, this, &ACannon::ShootRot, 1, false);

		isShootReady = false;
	}
	else
	{
		return;
	}
}

void ACannon::CannonShoot(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//대포에 닿은 액터가 playerbomb이면
	bomb = Cast<APlayerBomb>(OtherActor);
	if (bomb != nullptr)
	{
		//대포에 닿은 폭탄을 제거
		bomb->Destroy();

		

		//isShootReady를 true로 변환
		isShootReady = true;
	}
}

// void ACannon::ShootRot()
// {
// 	AddActorLocalRotation(FRotator(0, 0, 30));
// }

