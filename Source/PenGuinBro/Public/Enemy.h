// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class PENGUINBRO_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Enemy Settings")
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, Category = "Enemy Settings")
	class UStaticMeshComponent* meshComp;


	FVector direction = FVector(0, 1, 0);
	//FVector direction = GetActorForwardVector();
	float moveSpeed = 50;

	UFUNCTION()
	void TongOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
