// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverGhost.h"
#include "Components/SphereComponent.h"
#include "Components/MeshComponent.h"
#include "PlayerPenguin.h"
#include "EngineUtils.h"
#include "MyPenguinGameModeBase.h"
#include "Kismet/Gameplaystatics.h"

// Sets default values
AGameOverGhost::AGameOverGhost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SetRootComponent(sphereComp);
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGameOverGhost::BeginPlay()
{
	Super::BeginPlay();

	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AGameOverGhost::GhostOverlap);
	sphereComp->SetGenerateOverlapEvents(true);
}

// Called every frame
void AGameOverGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime += DeltaTime;

	if (currentTime > 0)
	{
		for (TActorIterator<APlayerPenguin> it(GetWorld()); it; ++it)
		{
			target = *it;
		}
		if (target != nullptr)
		{
			float temp = target->moveSpeed;
		}
		if (target != nullptr)
		{
			//플레이어위치 - 나의 위치 = 갈 방향을 설정
			FVector targetDir = target->GetActorLocation() - GetActorLocation();

			targetDir.Normalize();
	
			direction = targetDir;
		}
	}
	else
	{
		//정면으로 방향을 정한다
		direction = GetActorForwardVector();
	}

	SetActorLocation(GetActorLocation() + direction * moveSpeed * DeltaTime);
}

void AGameOverGhost::GhostOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerPenguin* player = Cast<APlayerPenguin>(OtherActor);

	if (player != nullptr)
	{
		player->Destroy();

		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
		AMyPenguinGameModeBase* myGM = Cast<AMyPenguinGameModeBase>(gm);
		myGM->LifeTime(1);
	}
}

