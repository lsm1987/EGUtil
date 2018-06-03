// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EGSnsGameModeBase.generated.h"

enum class EEGSnsServiceType : int32;

/**
 * SNS Plugin 테스트용 GameMode
 */
UCLASS()
class EGUTIL_API AEGSnsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	// SNS //////////////
public:
	void InitializeSns();
	void FinalizeSns();

private:
	FDelegateHandle OnLoggedInHandle;
	FDelegateHandle OnSharedHandle;

	void OnLoggedIn(EEGSnsServiceType ServiceType, bool bSuccess);
	void OnShared(EEGSnsServiceType ServiceType, bool bSuccess, const FString& ErrorMessage);

public:
	static FString GetScreenshotFilePath();
};
