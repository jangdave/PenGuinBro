// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyPenguinGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PENGUINBRO_API AMyPenguinGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override; 
	
	UPROPERTY(EditAnywhere, Category=MyDefaultSetting)
	TSubclassOf<class UMainWidget> mainwidget;

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetGameTimer(){ return gameTimer; }

	void GameTimer(int32 time);


private:
	int32 gameTimer = 90;
	
	class UMainWidget* main_UI;

	int32 currentTime = 0;
};
