// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerSpawner.generated.h"

UCLASS()
class PENGUINBRO_API APlayerSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=SpawnerSettings)
	class USceneComponent* sceneComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=SpawnerSettings)
	class UArrowComponent* arrowComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=SpawnerSettings)
	TSubclassOf<class APlayerPenguin> player;

private:
	void playerSpawn(int32 lifecount);
};
