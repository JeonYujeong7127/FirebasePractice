#include "FirebaseHelper.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

void UFirebaseHelper::AuthenticateWithFirebase(const FString& Email, const FString& Password, TFunction<void(FString)> OnSuccess, TFunction<void(FString)> OnError)
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(TEXT("https://identitytoolkit.googleapis.com/v1/accounts:signInWithPassword?key=AIzaSyDQwAfRNicdRUOaZTE2L6EDZqJHA5qMlM4"));
    Request->SetVerb(TEXT("POST"));
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

    FString Payload = FString::Printf(TEXT("{\"email\":\"%s\", \"password\":\"%s\", \"returnSecureToken\":true}"), *Email, *Password);
    Request->SetContentAsString(Payload);

    Request->OnProcessRequestComplete().BindLambda([OnSuccess, OnError](FHttpRequestPtr, const FHttpResponsePtr& Response, const bool bWasSuccessful)
    {
        if (bWasSuccessful && Response->GetResponseCode() == 200)
        {
            TSharedPtr<FJsonObject> JsonObject;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
            if (FJsonSerializer::Deserialize(Reader, JsonObject))
            {
                const FString IdToken = JsonObject->GetStringField(TEXT("idToken"));
                OnSuccess(IdToken);
                return;
            }
        }
        OnError(Response->GetContentAsString());
    });

    Request->ProcessRequest();
}

void UFirebaseHelper::SavePlayerScore(const FString& PlayerID, const int32 Score, const FString& IDToken, TFunction<void()> OnSuccess, TFunction<void(FString)> OnError)
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(FString::Printf(TEXT("https://fir-practice-cdf33-default-rtdb.firebaseio.com/scores/%s.json?auth=%s"), *PlayerID, *IDToken));
    Request->SetVerb(TEXT("PUT"));
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

    FString Payload = FString::Printf(TEXT("{\"score\":%d}"), Score);
    Request->SetContentAsString(Payload);

    Request->OnProcessRequestComplete().BindLambda([OnSuccess, OnError](FHttpRequestPtr, const FHttpResponsePtr& Response, bool bWasSuccessful)
    {
        if (bWasSuccessful && Response->GetResponseCode() == 200)
        {
            OnSuccess();
        }
        else
        {
            OnError(Response->GetContentAsString());
        }
    });

    Request->ProcessRequest();
}

void UFirebaseHelper::GetScores(const FString& IDToken, TFunction<void(TMap<FString, int32>)> OnSuccess, TFunction<void(FString)> OnError)
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(FString::Printf(TEXT("https://fir-practice-cdf33-default-rtdb.firebaseio.com/scores.json?auth=%s"), *IDToken));
    Request->SetVerb(TEXT("GET"));

    Request->OnProcessRequestComplete().BindLambda([OnSuccess, OnError](FHttpRequestPtr, const FHttpResponsePtr& Response, bool bWasSuccessful)
    {
        if (bWasSuccessful && Response->GetResponseCode() == 200)
        {
            TSharedPtr<FJsonObject> JsonObject;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
            if (FJsonSerializer::Deserialize(Reader, JsonObject))
            {
                TMap<FString, int32> Scores;
                for (const auto& Pair : JsonObject->Values)
                {
                    FString PlayerID = Pair.Key;
                    int32 Score = JsonObject->GetIntegerField(TEXT("score"));
                    Scores.Add(PlayerID, Score);
                }
                OnSuccess(Scores);
                return;
            }
        }
        OnError(Response->GetContentAsString());
    });

    Request->ProcessRequest();
}
