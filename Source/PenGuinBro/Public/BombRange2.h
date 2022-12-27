// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BombRange2.generated.h"

UCLASS()
class PENGUINBRO_API ABombRange2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABombRange2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = BombRangeSettings)
	class USphereComponent* sphereComp1;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = BombRangeSettings)
	class USphereComponent* sphereComp2;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = BombRangeSettings)
	class UStaticMeshComponent* meshComp;

};
