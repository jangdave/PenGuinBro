// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BombRangeOne.generated.h"

UCLASS()
class PENGUINBRO_API ABombRangeOne : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABombRangeOne();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = BombRangeSettings)
	class USphereComponent* sphereComp;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = BombRangeSettings)
	class USphereComponent* sphereComp1;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = BombRangeSettings)
	class UStaticMeshComponent* meshComp;
	
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = BombRangeSettings)
	class UStaticMeshComponent* meshComp1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = BombRangeSettings)
	class UParticleSystem* explosion_effect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = BombRangeSettings)
	class UParticleSystem* explosion_effect1;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	float currentTime = 0;

	float explosionTime = 0.5f;

	FTimerHandle exploTimer;

	void esplosionTimer();

};
