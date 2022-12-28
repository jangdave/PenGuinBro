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
	
	UPROPERTY(EditDefaultsOnly, Category=PlayerSettings)
	class UInputAction* ia_Horizental;

	UPROPERTY(EditDefaultsOnly, Category=PlayerSettings)
	class UInputAction* ia_Up;

	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
	class UInputAction* ia_Down;

	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
	class UInputAction* ia_BombDrop;

	float H;

	FVector direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
	class UBoxComponent* boxComp;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UFUNCTION(BlueprintCallable)
	void Horizental(float val);

	UFUNCTION(BlueprintCallable)
	void Up();

	UFUNCTION(BlueprintCallable)
	void Down();

	UFUNCTION(BlueprintCallable)
	void BombDrop();

};
