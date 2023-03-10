// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishCoin.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "FinishLine.h"
#include "PlayerPenGuin.h"
#include "EndWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFinishCoin::AFinishCoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp=CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Coll"));
	SetRootComponent(sphereComp);
	meshComp=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFinishCoin::BeginPlay()
{
	Super::BeginPlay();

	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AFinishCoin::FinishTouch);
	sphereComp->SetGenerateOverlapEvents(true);
}

// Called every frame
void AFinishCoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFinishCoin::FinishTouch(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFinishLine* endline = Cast<AFinishLine>(OtherActor);
	APlayerPenguin* player = Cast<APlayerPenguin>(OtherActor);

	if (endline != nullptr)
	{
		//부착시킨다
		this->AttachToActor(endline, FAttachmentTransformRules::SnapToTargetIncludingScale);
		
		//end위젯 불러오기
		end_UI = CreateWidget<UEndWidget>(GetWorld(), endwidget);

		if (end_UI != nullptr)
		{
			end_UI->AddToViewport();
		}

		UGameplayStatics::PlaySound2D(this, endSound);

		//게임시간 스탑
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0);
	}
	
	if (player != nullptr)
	{
		this->AttachToActor(player, FAttachmentTransformRules::SnapToTargetIncludingScale);

		FTimerHandle disTimer;

		GetWorld()->GetTimerManager().SetTimer(disTimer, this, &AFinishCoin::ResetAttach, 2.0f, false);
	}
}

void AFinishCoin::ResetAttach()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

