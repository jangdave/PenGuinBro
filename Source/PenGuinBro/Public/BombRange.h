// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BombRange.generated.h"

UCLASS()
class PENGUINBRO_API ABombRange : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABombRange();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = BombRangeSettings)
	class USphereComponent* sphereComp;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = BombRangeSettings)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = BombRangeSettings)
	class UParticleSystem* explosion_effect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BombSettings)
	TSubclassOf<class ABombRangeOne> bombRangeone;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
