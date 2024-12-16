// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FirebaseHelper.generated.h"

/**
 * 
 */
UCLASS()
class FIREBASEPRACTICE_API UFirebaseHelper : public UObject
{
	GENERATED_BODY()

public:
	// 로그인 함수
	static void AuthenticateWithFirebase(const FString& Email, const FString& Password, TFunction<void(FString)> OnSuccess, TFunction<void(FString)> OnError);

	// 데이터 저장 함수
	static void SavePlayerScore(const FString& PlayerID, int32 Score, const FString& IDToken, TFunction<void()> OnSuccess, TFunction<void(FString)> OnError);

	// 데이터 읽기 함수
	static void GetScores(const FString& IDToken, TFunction<void(TMap<FString, int32>)> OnSuccess, TFunction<void(FString)> OnError);

};
