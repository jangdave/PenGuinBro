// Fill out your copyright notice in the Description page of Project Settings.


#include "BombRangeOne.h"
#include "Components/SphereComponent.h"
#include "Components/MeshComponent.h"
#include "Kismet/Gameplaystatics.h"
#include "Enemy.h"
#include "PlayerPenGuin.h"
#include "Tong.h"
#include "MyPenguinGameModeBase.h"

// Sets default values
ABombRangeOne::ABombRangeOne()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SetRootComponent(sphereComp);
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(sphereComp);
	sphereComp1 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision1"));
	sphereComp1->SetupAttachment(sphereComp);
	meshComp1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh1"));
	meshComp1->SetupAttachment(sphereComp1);
}

// Called when the game starts or when spawned
void ABombRangeOne::BeginPlay()
{
	Super::BeginPlay();

	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABombRangeOne::OnOverlap);
	sphereComp->SetGenerateOverlapEvents(true);
	sphereComp1->OnComponentBeginOverlap.AddDynamic(this, &ABombRangeOne::OnOverlap);
	sphereComp1->SetGenerateOverlapEvents(true);

	GetWorld()->GetTimerManager().SetTimer(exploTimer, this, &ABombRangeOne::esplosionTimer, 0.2f, false);
}

// Called every frame
void ABombRangeOne::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime += DeltaTime;

	if (currentTime > explosionTime)
	{		
		Destroy();

		//누적된 시간을 다시 0으로 초기화
		currentTime = 0;
	}

}

void ABombRangeOne::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy* enemy = Cast<AEnemy>(OtherActor);
	APlayerPenguin* enemy1 = Cast<APlayerPenguin>(OtherActor);
	ATong* tong = Cast<ATong>(OtherActor);

	if (enemy != nullptr)
	{
		enemy->Destroy();
	}
	else if (enemy1 != nullptr)
	{
		enemy1->Destroy();
		
		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
		AMyPenguinGameModeBase* myGM = Cast<AMyPenguinGameModeBase>(gm);
		myGM->LifeTime(1);
	}
	else if (tong != nullptr)
	{
		tong->Destroy();
	}
}

void ABombRangeOne::esplosionTimer()
{
	FVector effectLoc = GetActorLocation() + GetActorUpVector() * 10.0f;
	FRotator effectRot = GetActorRotation();

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion_effect, effectLoc, effectRot, true);

	FVector effectLoc1 = GetActorLocation() + GetActorRightVector() * 140.0f + GetActorUpVector() * 10.0f;
	FRotator effectRot1 = FRotator(0, 0, 0);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion_effect1, effectLoc1, effectRot1, true);
}

