// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPenguinGameModeBase.h"
#include "MainWidget.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerPenGuin.h"
#include "EngineUtils.h"
#include "OverWidget.h"
#include "GameOverGhost.h"

AMyPenguinGameModeBase::AMyPenguinGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyPenguinGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	main_UI = CreateWidget<UMainWidget>(GetWorld(), mainwidget);
	
	if (main_UI != nullptr)
	{
		main_UI->AddToViewport();

		main_UI->PrintMainGame();
	}
}

void AMyPenguinGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (gameTimer > 0)
	{
		GameTimer(DeltaTime);
	}
	else
	{
		if (stop != true)
		{
			GameTimer(DeltaTime);

		}
	}
	if (start != false)
	{
		OverTime(DeltaTime);
	}
}

void AMyPenguinGameModeBase::GameTimer(float time)
{
	gameTimer -= time;
	if (gameTimer <= 0)
	{
		gameTimer = 0.00f;

		stop = true;

		//�ð����� �ͽ� ��ȯ
		FActorSpawnParameters SpawnParams;
		GetWorld()->SpawnActor<AGameOverGhost>(ghost, FVector(800.0f, 0.0f, -40.0f), FRotator(0, 0, 0), SpawnParams);
	}
	if (main_UI != nullptr)
	{
		main_UI->PrintMainGame();
	}
}

void AMyPenguinGameModeBase::LifeTime(int32 count)
{	
	if(lifeTime > 0)
	{
		lifeTime -= count;

		FActorSpawnParameters SpawnParams;
		//ĳ���� ����
		GetWorld()->SpawnActor<APlayerPenguin>(player, FVector(808.0f, -370.0f, -184.0f), FRotator(0, 0, 0), SpawnParams);
		GetWorld()->SpawnPlayActor<APlayerPenguin>(player, )
	}
	else
	{
		//���ӿ���
		over_UI = CreateWidget<UOverWidget>(GetWorld(), overwidget);

		start = true;

		if (over_UI != nullptr)
		{
			over_UI->AddToViewport();

			over_UI->PrintOverGame();
		}

		//Ư��Ű ������ ���� ����
	}
	if (main_UI != nullptr)
	{
		main_UI->PrintMainGame();
	}
}

void AMyPenguinGameModeBase::OverTime(float otime)
{
	//�ð� �����ϱ�
	UE_LOG(LogTemp,Warning,TEXT("%f"), otime);

	overTime -= otime;

	if (overTime <= 0)
	{
		overTime = 0.00f;
	}
	
	if (over_UI != nullptr)
	{
		over_UI->PrintOverGame();
	}
}

