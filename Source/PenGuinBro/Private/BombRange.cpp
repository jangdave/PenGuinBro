// Fill out your copyright notice in the Description page of Project Settings.


#include "BombRange.h"
#include "Components/SphereComponent.h"
#include "Components/MeshComponent.h"
#include "Enemy.h"
#include "Kismet/Gameplaystatics.h"
#include "BombRangeOne.h"
#include "PlayerPenGuin.h"
#include "Tong.h"
#include "MyPenguinGameModeBase.h"

// Sets default values
ABombRange::ABombRange()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SetRootComponent(sphereComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABombRange::BeginPlay()
{
	Super::BeginPlay();
	
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABombRange::OnOverlap);
	sphereComp->SetGenerateOverlapEvents(true);

	FVector effectLoc = GetActorLocation();
	FRotator effectRot = GetActorRotation();

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion_effect, effectLoc, effectRot, true);

	FVector spawnPosition = GetActorLocation() + GetActorRightVector() * (-70.0f);
	FRotator spawnRotation = FRotator(0, 0, 0);
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<ABombRangeOne>(bombRangeone, spawnPosition, spawnRotation, param);

	GetWorld()->GetTimerManager().SetTimer(disTimer, this, &ABombRange::DestroyMyself, 0.4f, false);
}

// Called every frame
void ABombRange::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABombRange::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
		//enemy1->SetActorLocation(FVector(808.0f, -370.0f, -184.0f));
		//enemy1->SetActorRotation(FRotator(0, 90.0f, 0));

		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
		AMyPenguinGameModeBase* myGM = Cast<AMyPenguinGameModeBase>(gm);
		myGM->LifeTime(1);
	}
	else if (tong != nullptr)
	{
		tong->Destroy();
	}
	UGameplayStatics::PlaySound2D(this, fireSound);
}

void ABombRange::DestroyMyself()
{
	Destroy();
}
