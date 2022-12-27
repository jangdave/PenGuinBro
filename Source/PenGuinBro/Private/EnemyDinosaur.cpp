// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyDinosaur.h"
#include "Components/BoxComponent.h"
#include "BombRange.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/Gameplaystatics.h"

// Sets default values
AEnemyDinosaur::AEnemyDinosaur()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(25.0f, 25.0f, 35.0f));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemyDinosaur::BeginPlay()
{
	Super::BeginPlay();

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyDinosaur::OnOverlap);
	boxComp->SetGenerateOverlapEvents(true);
	
}

// Called every frame
void AEnemyDinosaur::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	direction = GetActorForwardVector();


	SetActorLocation(GetActorLocation() + direction * moveSpeed * DeltaTime);


}

// Called to bind functionality to input
void AEnemyDinosaur::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyDinosaur::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

