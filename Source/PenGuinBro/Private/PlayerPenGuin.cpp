// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPenguin.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerBomb.h"
#include "Components/BoxComponent.h"
#include "RotFloor.h"
#include "GameFramework/Actor.h"

// Sets default values
APlayerPenguin::APlayerPenguin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision for RotFloor"));
	boxComp->SetupAttachment(RootComponent);
	boxComp->SetBoxExtent(FVector(5.0f));

}

// Called when the game starts or when spawned
void APlayerPenguin::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &APlayerPenguin::OnOverlap);
}

// Called every frame
void APlayerPenguin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	direction.Normalize();

	FVector dir = GetActorLocation() + direction * moveSpeed * DeltaTime;
	SetActorLocation(dir);

	rotTime += DeltaTime;

	UE_LOG(LogTemp, Warning, TEXT("%f"), rotTime);
}

// Called to bind functionality to input
void APlayerPenguin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerPenguin::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARotFloor* rotFloor = Cast<ARotFloor>(OtherActor);
	if (rotFloor != nullptr)
	{
		//플레이어를 X축으로 180도 회전시키고
		SetActorRotation(FRotator(180,0,0));

		//회전발판에 Attach 시킨다.
		//AttachToActor(rotFloor, FAttachmentTransformRules::SnapToTargetIncludingScale);

		UE_LOG(LogTemp, Warning, TEXT("Overlap"));

		
		rotFloor->SetActorTickEnabled(true);
		if (rotTime >= 1.0f)
		{
			rotFloor->SetActorTickEnabled(false);
			rotTime = 0;
		};
		

		
		
	}
	
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
	FVector spawnPosition = GetActorLocation() + GetActorForwardVector() * 50.0f;
	FRotator spawnRotation = FRotator(20.0f, 0, 0);
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<APlayerBomb>(bombFactory, spawnPosition, spawnRotation, param);
}




//AdddMovementInput 벽에 비벼지지 않게 하는 기능