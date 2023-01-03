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
	AMyPenguinGameModeBase();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override; 
	
	UPROPERTY(EditAnywhere, Category=MyDefaultSetting)
	TSubclassOf<class UMainWidget> mainwidget;

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetGameTimer(){ return gameTimer; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetLifeTime(){ return lifeTime; }

	void GameTimer(float time);

	void LifeTime(int32 count);


private:
	int32 lifeTime = 2;
	
	float gameTimer = 91;

	class UMainWidget* main_UI;

	class AActor* target;
};
