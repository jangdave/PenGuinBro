// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerPenguin.generated.h"

UCLASS()
class PENGUINBRO_API APlayerPenguin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerPenguin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
	TSubclassOf<class APlayerBomb> bombFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
	float moveSpeed = 200;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
	class UBoxComponent* boxCompF;
	
	FVector direction;

	class ARotFloor* rotFloor;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void ResetAttach();

	UFUNCTION()
	void ResetGravity();

	bool isOnFloor = false;

private:
	UFUNCTION(BlueprintCallable)
	void BombDrop();

	float rotTime = 0;
	float rotCool = 1.0f;
	bool isTouched;
};
