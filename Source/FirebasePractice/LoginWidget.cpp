// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginWidget.h"
#include "FirebaseHelper.h"
#include "FirebasePracticeCharacter.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"

void ULoginWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (BT_Login)
	{
		BT_Login->OnClicked.AddDynamic(this, &ULoginWidget::Login);
	}
}

void ULoginWidget::Login()
{
	FString UserID = ETB_ID->GetText().ToString();
	FString UserPassword = ETB_Password->GetText().ToString();
	
	UFirebaseHelper::AuthenticateWithFirebase(
		UserID,
		UserPassword,
		[this](FString IDToken)
		{
			UE_LOG(LogTemp, Log, TEXT("Login Successful! ID Token: %s"), *IDToken);
			bIsLogin = true;
			this->FirebaseIDToken = IDToken;
			Cast<AFirebasePracticeCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter())->SetIDToken(IDToken);
			TB_LoginResult->SetText(FText::FromString(TEXT("Login Succeed!")));
			Popup();
		},
		[this](const FString& ErrorMessage)
		{
			UE_LOG(LogTemp, Error, TEXT("Login Failed: %s"), *ErrorMessage);
			bIsLogin = false;
			TB_LoginResult->SetText(FText::FromString(TEXT("Login Failed")));
			
			OV_Popup->SetVisibility(ESlateVisibility::Visible);
			Popup();
		}
	);
}

void ULoginWidget::Popup()
{
	OV_Popup->SetVisibility(ESlateVisibility::Visible);
	FTimerHandle PopupTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(PopupTimerHandle, FTimerDelegate::CreateLambda([this]
	{
		OV_Popup->SetVisibility(ESlateVisibility::Hidden);
		if(bIsLogin)
		{
			RemoveFromParent();
		}
	}), 3.0f, false);
}
