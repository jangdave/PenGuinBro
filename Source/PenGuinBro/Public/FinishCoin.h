// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FinishCoin.generated.h"

UCLASS()
class PENGUINBRO_API AFinishCoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFinishCoin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CoinSettings)
	class USphereComponent* sphereComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CoinSettings)
	class UStaticMeshComponent* meshComp;

	UFUNCTION()
	void FinishTouch(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere, Category=CoinSettings)
	TSubclassOf<class UEndWidget> endwidget;

	UPROPERTY(EditDefaultsOnly, Category = CoinSettings)
	class USoundBase* endSound;

	UFUNCTION()
	void ResetAttach();

	class UEndWidget* end_UI;
};
