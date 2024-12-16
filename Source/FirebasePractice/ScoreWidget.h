// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class FIREBASEPRACTICE_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ScoreSend();
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UEditableTextBox> ETB_Score;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UButton> BT_Send;
};
