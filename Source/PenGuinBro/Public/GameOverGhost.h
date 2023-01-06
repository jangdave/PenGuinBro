// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameOverGhost.generated.h"

UCLASS()
class PENGUINBRO_API AGameOverGhost : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameOverGhost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = GhostSettings)
	class USphereComponent* sphereComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = GhostSettings)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditDefaultsOnly, Category = MyDefaultSetting)
	class USoundBase* ghostSound;

	FVector direction;

	float moveSpeed = 30.0f;

	class APlayerPenguin* target;

	float currentTime = 0;

	UFUNCTION()
	void GhostOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
