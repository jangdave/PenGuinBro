// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MyPenguinGameModeBase.h"
#include "Components/TextBlock.h"

void UMainWidget::PrintGameTimer()
{
	AMyPenguinGameModeBase* myGM = Cast<AMyPenguinGameModeBase>(UGameplayStatics::GetGameMode(this));
	
	if (myGM != nullptr)
	{
		FText timer = FText::AsNumber(myGM->GetGameTimer());
		gamTimer->SetText(timer);
	}
}
