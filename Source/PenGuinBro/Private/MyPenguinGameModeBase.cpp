// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPenguinGameModeBase.h"
#include "MainWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MyPenguinGameModeBase.h"

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
	
	GameTimer(DeltaTime);
}

void AMyPenguinGameModeBase::GameTimer(float time)
{
	gameTimer -= time;
	
	if (gameTimer <= 0)
	{
		gameTimer = 0.00f;
	}
	if (main_UI != nullptr)
	{
		main_UI->PrintMainGame();
	}
}

void AMyPenguinGameModeBase::LifeTime(int32 count)
{
	//캐릭터 불러와서 사라지면 라이프 타임이 1씩 줄어듬
	lifeTime -= 1;

	if (main_UI != nullptr)
	{
		main_UI->PrintMainGame();
	}
}

