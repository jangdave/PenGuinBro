// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotFloor.generated.h"

UCLASS()
class PENGUINBRO_API ARotFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RotFloor Settings")
	class UBoxComponent* boxCompR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotFloor Settings")
	class UStaticMeshComponent* meshCompR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotFloor Settings")
	FVector direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotFloor Settings")
	float rotSpeed;
};