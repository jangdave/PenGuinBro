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

	//��Ʈ�ѷ� �����̼� ���
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

	//������ �ڽ��� ȸ�����ǿ� �������Ǹ� -> isTouched�� Ʈ���
	if (isTouched){
		//ȸ�������� ƽ�� Ȱ��ȭ ��Ų��.
		rotFloor->SetActorTickEnabled(true);

		rotTime += DeltaTime;
		//�����̼� Ÿ���� 1�ʺ��� ũ�ų� ��������
		//if (rotTime >= 1.0f)
		//{
		//ȸ�������� ƽ�� ��Ȱ��ȭ ��Ű��
		//	rotFloor->SetActorTickEnabled(false);
		//�����̼� Ÿ���� 0���� �ʱ�ȭ��Ų��.
		//	rotTime = 0;
		//	isTouched = false;
		//};

		//ȸ�� �ð��� 1�ʿ� ���������
		if (rotTime >= 0.95f)
		{
			//ȸ�������� ƽ�� ��Ȱ��ȭ ��Ű��
			rotFloor->SetActorTickEnabled(false);
			rotFloor->SetActorRotation(FRotator(0,0,180));
			//�����̼� Ÿ���� 0���� �ʱ�ȭ��Ų��.
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
	//������ �̺�Ʈ�� �ƴ����͸� ȸ�����ǿ� ĳ���� �� �� ������
	rotFloor = Cast<ARotFloor>(OtherActor);

	
	if (rotFloor != nullptr)
	{
		//�÷��̾ X������ 180�� ȸ����Ű��
		SetActorRotation(FRotator(180, 0, 0));

		GetCharacterMovement()->GravityScale = 0;

		//ȸ�����ǿ� Attach ��Ų��.
		AttachToActor(rotFloor, FAttachmentTransformRules::KeepWorldTransform);

		FTimerHandle gravityTimer;
		GetWorld()->GetTimerManager().SetTimer(gravityTimer, this, &APlayerPenguin::ResetGravity, 1, false);

		FTimerHandle snapTimer;
		GetWorld()->GetTimerManager().SetTimer(snapTimer, this, &APlayerPenguin::ResetAttach, 2, false);

		//isTouched�� Ʈ��� ó��
		isTouched = true;
		//UE_LOG(LogTemp, Warning, TEXT("Overlap"));
	}
	
}

void APlayerPenguin::ResetAttach()
{
	//�ٿ����� �θ� �����Ѵ�.
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

//AdddMovementInput ���� ������ �ʰ� �ϴ� ���