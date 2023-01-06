// Fill out your copyright notice in the Description page of Project Settings.


#include "OverWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MyPenguinGameModeBase.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UOverWidget::PrintOverGame()
{
	AMyPenguinGameModeBase* myGM = Cast<AMyPenguinGameModeBase>(UGameplayStatics::GetGameMode(this));

	if (myGM != nullptr)
	{
		FText otimer = FText::AsNumber(myGM->GetOverTime());
		gameOver->SetText(otimer);

		UGameplayStatics::PlaySound2D(this, overSound);
	}
}

void UOverWidget::LevelReset()
{
	//레벨을 다시 로드한다
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("1-1"));
}
