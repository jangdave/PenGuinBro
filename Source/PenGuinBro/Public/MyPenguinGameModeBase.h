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
	
	UPROPERTY(EditAnywhere, Category=MyDefaultSetting)
	TSubclassOf<class UOverWidget> overwidget;

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetGameTimer(){ return gameTimer; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetLifeTime(){ return lifeTime; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetOverTime(){ return overTime; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=MyDefaultSetting)
	TSubclassOf<class APlayerPenguin> player;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=MyDefaultSetting)
	TSubclassOf<class AGameOverGhost> ghost;

	void GameTimer(float time);

	void LifeTime(int32 count);

	void OverTime(float otime);

	class AEnemyDinosaur* enemies;

private:
	int32 lifeTime = 2;

	float gameTimer = 91;
	
	float overTime = 21;

	class UMainWidget* main_UI;
	
	class UOverWidget* over_UI;
	
	class AActor* target;

	float currentTime = 0;

	bool stop = false;

	bool start = false;
};
