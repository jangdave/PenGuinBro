// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPenguin.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerBomb.h"


// Sets default values
APlayerPenguin::APlayerPenguin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerPenguin::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPenguin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	direction.Normalize();

	FVector dir = GetActorLocation() + direction * moveSpeed * DeltaTime;
	SetActorLocation(dir);

}

// Called to bind functionality to input
void APlayerPenguin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerPenguin::Horizental(float value)
{
	H = value;
	UE_LOG(LogTemp, Warning, TEXT("H : %.4f"), H);
	direction.Y = H;

}

void APlayerPenguin::Up()
{

}

void APlayerPenguin::Down()
{

}

void APlayerPenguin::BombDrop()
{
	FVector spawnPosition = GetActorLocation() + GetActorForwardVector() * 40.0f;
	FRotator spawnRotation = FRotator(10.0f, 0, 0);
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<APlayerBomb>(bombFactory, spawnPosition, spawnRotation, param);
}




//AdddMovementInput 벽에 비벼지지 않게 하는 기능