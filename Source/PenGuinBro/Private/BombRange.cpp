// Fill out your copyright notice in the Description page of Project Settings.


#include "BombRange.h"
#include "Components/SphereComponent.h"
#include "Components/MeshComponent.h"
#include "EnemyDinosaur.h"
#include "Kismet/Gameplaystatics.h"

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
}

// Called every frame
void ABombRange::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GetWorld()->SpawnActor<ABombRange2>(bombRange2, GetActorTransform());

}

void ABombRange::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemyDinosaur* enemy = Cast<AEnemyDinosaur>(OtherActor);

	if (enemy != nullptr)
	{		
		enemy->Destroy();

		Destroy();
	}
}

//FVector effectLoc = GetActorLocation();
//FRotator effectRot = GetActorRotation();

//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion_effect, effectLoc, effectRot, true);