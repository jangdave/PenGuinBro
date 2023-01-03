// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPenguinGameModeBase.h"
#include "MainWidget.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerPenGuin.h"
#include "EngineUtils.h"

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
	if(lifeTime >= 0)
	{
		lifeTime -= count;

		//플레이어 부활
	}
	else
	{
		//게임오버
	}
	if (main_UI != nullptr)
	{
		main_UI->PrintMainGame();
	}
}

