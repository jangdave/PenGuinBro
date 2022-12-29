// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPenguinGameModeBase.h"
#include "MainWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MyPenguinGameModeBase.h"

void AMyPenguinGameModeBase::BeginPlay()
{
	main_UI = CreateWidget<UMainWidget>(GetWorld(), mainwidget);
	
	if (main_UI != nullptr)
	{
		main_UI->AddToViewport();

		main_UI->PrintGameTimer();
	}
}

void AMyPenguinGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime += DeltaTime;

	//AMyPenguinGameModeBase::GameTimer;
	//GameTimer(1);
}

void AMyPenguinGameModeBase::GameTimer(int32 time)
{
	gameTimer -= time;
	
	if(main_UI != nullptr)
	{
		main_UI->PrintGameTimer();
	}
}

