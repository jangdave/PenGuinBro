// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndWidget.generated.h"

/**
 * 
 */
UCLASS()
class PENGUINBRO_API UEndWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting|End", meta = (BindWidget))
	class UTextBlock* endGame;
	
};
