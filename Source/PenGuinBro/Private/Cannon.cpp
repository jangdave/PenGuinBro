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

	//isShootReady�� ���̸�
	if (isShootReady) {
		//�� �ַο� ��ġ�� �������� playerbomb�� �����ϰ�
		GetWorld()->SpawnActor<APlayerBomb>(bombFactory, shootArrow->GetComponentLocation(), shootArrow->GetComponentRotation());
		//isShootReady�� �������� �ٲ�

		//1�� �� ������ ������ ������
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
	//������ ���� ���Ͱ� playerbomb�̸�
	bomb = Cast<APlayerBomb>(OtherActor);
	if (bomb != nullptr)
	{
		//������ ���� ��ź�� ����
		bomb->Destroy();

		

		//isShootReady�� true�� ��ȯ
		isShootReady = true;
	}
}

// void ACannon::ShootRot()
// {
// 	AddActorLocalRotation(FRotator(0, 0, 30));
// }

