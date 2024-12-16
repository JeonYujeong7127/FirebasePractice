// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"

#include "FirebaseHelper.h"
#include "FirebasePracticeCharacter.h"

void UScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BT_Send->OnClicked.AddDynamic(this, &UScoreWidget::ScoreSend);
}

void UScoreWidget::ScoreSend()
{
	int Score = FCString::Atoi(*ETB_Score->GetText().ToString());

	FString IDToken = Cast<AFirebasePracticeCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter())->GetIDToken();
	FString Name = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetName();
	UFirebaseHelper::SavePlayerScore(
		Name,
		Score,
		IDToken,
		[Score]()
		{
			UE_LOG(LogTemp, Log, TEXT("Save Score Success! Score: %d"), Score);
		},
		[Score](const FString& ErrorMessage)
		{
			UE_LOG(LogTemp, Log, TEXT("Save Score Failed! IDToken: %d"), Score);
		}
	);	
}
