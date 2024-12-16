// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginWidget.generated.h"

/**
 * 
 */
UCLASS()
class FIREBASEPRACTICE_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void Login();

	UFUNCTION()
	void Popup();
	
	bool bIsLogin = false;
	
private:
	FString FirebaseIDToken;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UEditableTextBox> ETB_ID;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UEditableTextBox> ETB_Password;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UButton> BT_Login;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UOverlay> OV_Popup;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UTextBlock> TB_LoginResult;
};
