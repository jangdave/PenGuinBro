// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPenguin.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerBomb.h"
#include "Components/BoxComponent.h"
#include "RotFloor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/Gameplaystatics.h"

// Sets default values
APlayerPenguin::APlayerPenguin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision for RotFloor"));
	boxComp->SetupAttachment(RootComponent);
	boxComp->SetBoxExtent(FVector(5.0f));

	//컨트롤러 로테이션 상속
	//bUseControllerRotationYaw(true);
}

// Called when the game starts or when spawned
void APlayerPenguin::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &APlayerPenguin::OnOverlap);

	GetWorld()->GetFirstPlayerController()->Possess(this);

	startlocation = GetActorLocation();
}

// Called every frame
void APlayerPenguin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//direction.Normalize();

	//FVector dir = GetActorLocation() + direction * moveSpeed * DeltaTime;
	//SetActorLocation(dir);

	//정수리 박스가 회전발판에 오버랩되면 -> isTouched가 트루면
	if (isTouched){
		//회전발판의 틱을 활성화 시킨다.
		rotFloor->SetActorTickEnabled(true);

		rotTime += DeltaTime;
		//로테이션 타임이 1초보다 크거나 같아지면
		//if (rotTime >= 1.0f)
		//{
		//회전발판의 틱을 비활성화 시키고
		//	rotFloor->SetActorTickEnabled(false);
		//로테이션 타임을 0으로 초기화시킨다.
		//	rotTime = 0;
		//	isTouched = false;
		//};

		//회전 시간이 1초에 가까워지면
		if (rotTime >= 0.95f)
		{
			//회전발판의 틱을 비활성화 시키고
			rotFloor->SetActorTickEnabled(false);
			rotFloor->SetActorRotation(FRotator(0,0,180));
			//로테이션 타임을 0으로 초기화시킨다.
			rotTime = 0;
			isTouched = false;
		};
	}

	//UE_LOG(LogTemp, Warning, TEXT("%f"), rotTime);
}

// Called to bind functionality to input
void APlayerPenguin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("PushDown", IE_Pressed, this, &APlayerPenguin::PushDown);
	PlayerInputComponent->BindAction("Desh", IE_Pressed, this, &APlayerPenguin::Desh);
}

void APlayerPenguin::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//오버랩 이벤트의 아더액터를 회전발판에 캐스팅 할 수 있으면
	rotFloor = Cast<ARotFloor>(OtherActor);

	
	if (rotFloor != nullptr)
	{
		//플레이어를 X축으로 180도 회전시키고
		SetActorRotation(FRotator(180, 0, 0));

		GetCharacterMovement()->GravityScale = 0;

		//회전발판에 Attach 시킨다.
		AttachToActor(rotFloor, FAttachmentTransformRules::KeepWorldTransform);

		FTimerHandle gravityTimer;
		GetWorld()->GetTimerManager().SetTimer(gravityTimer, this, &APlayerPenguin::ResetGravity, 1, false);

		FTimerHandle snapTimer;
		GetWorld()->GetTimerManager().SetTimer(snapTimer, this, &APlayerPenguin::ResetAttach, 2, false);

		//isTouched를 트루로 처리
		isTouched = true;
		//UE_LOG(LogTemp, Warning, TEXT("Overlap"));
	}
	
}

void APlayerPenguin::ResetAttach()
{
	//붙여놨던 부모를 해제한다.
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	if (GetActorRotation() == FRotator(180, 0, 0))
	{
		AddActorWorldRotation(FRotator(-180,0,0));
	}
}

void APlayerPenguin::ResetGravity()
{
	GetCharacterMovement()->GravityScale = 1;
}

void APlayerPenguin::BombDrop()
{
	FVector spawnPosition = GetActorLocation() + GetActorForwardVector() * 50.0f;
	FRotator spawnRotation = FRotator(20.0f, 0, 0);
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<APlayerBomb>(bombFactory, spawnPosition, spawnRotation, param);
}

void APlayerPenguin::PushDown()
{
	
}

void APlayerPenguin::Desh()
{
	//LaunchCharacter(GetActorForwardVector(),true,false);
}

//AdddMovementInput 벽에 비벼지지 않게 하는 기능