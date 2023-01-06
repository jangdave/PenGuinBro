// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cannon.generated.h"

UCLASS()
class PENGUINBRO_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACannon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = CannonSettings)
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, Category = CannonSettings)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, Category = CannonSettings)
	class UArrowComponent* shootArrow;

	UPROPERTY(EditAnywhere, Category = CannonSettings)
	TSubclassOf<class APlayerBomb> bombFactory;

	UPROPERTY(EditAnywhere, Category = CannonSettings)
	float ImpulseForce;

	bool isShootReady = false;

	APlayerBomb* bomb;

	UFUNCTION()
	void CannonShoot(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

// 	UFUNCTION()
// 	void ShootRot();
};
