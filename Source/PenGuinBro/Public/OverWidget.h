// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverWidget.generated.h"

/**
 * 
 */
UCLASS()
class PENGUINBRO_API UOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting|Over", meta = (BindWidget))
	class UTextBlock* gameOver;

	void PrintOverGame();
	
};