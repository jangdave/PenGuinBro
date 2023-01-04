// Fill out your copyright notice in the Description page of Project Settings.


#include "OverWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MyPenguinGameModeBase.h"
#include "Components/TextBlock.h"

void UOverWidget::PrintOverGame()
{
	AMyPenguinGameModeBase* myGM = Cast<AMyPenguinGameModeBase>(UGameplayStatics::GetGameMode(this));

	if (myGM != nullptr)
	{
		FText otimer = FText::AsNumber(myGM->GetOverTime());
		gameOver->SetText(otimer);
	}
}
