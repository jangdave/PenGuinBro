// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class PENGUINBRO_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySetting|Timer", meta=(BindWidget))
	class UTextBlock* gamTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySetting|Life", meta=(BindWidget))
	class UTextBlock* lifeTime;

	void PrintMainGame();
};
