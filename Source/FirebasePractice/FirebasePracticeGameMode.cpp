// Copyright Epic Games, Inc. All Rights Reserved.

#include "FirebasePracticeGameMode.h"
#include "FirebasePracticeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFirebasePracticeGameMode::AFirebasePracticeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
