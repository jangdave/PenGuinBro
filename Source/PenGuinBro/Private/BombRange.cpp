// Fill out your copyright notice in the Description page of Project Settings.


#include "BombRange.h"
#include "Components/SphereComponent.h"
#include "Components/MeshComponent.h"
#include "EnemyDinosaur.h"
#include "Kismet/Gameplaystatics.h"
#include "BombRangeOne.h"
#include "PlayerPenGuin.h"

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

	GetWorld()->GetTimerManager().SetTimer(disTimer, this, &ABombRange::DestroyMyself, 1.0f, false);
}

// Called every frame
void ABombRange::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABombRange::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemyDinosaur* enemy = Cast<AEnemyDinosaur>(OtherActor);
	APlayerPenguin* enemy1 = Cast<APlayerPenguin>(OtherActor);
	if (enemy != nullptr)
	{		
		enemy->Destroy();
	}
	else if (enemy1 != nullptr)
	{
		enemy1->Destroy();
	}
}

void ABombRange::DestroyMyself()
{
	Destroy();
}
