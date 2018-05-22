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

	// Screenshot //////////////
private:
	FDelegateHandle OnScreenshotCapturedHandle;
	int32 ScreenshotWidth;
	int32 ScreenshotHeight;
	TArray<FColor> ScreenshotColors;

public:
	void RequestScreenshot();
private:
	void OnScreenshotCaptured(int32 Width, int32 Height, const TArray<FColor>& Colors);
	void SaveScreenshotToFile();
	void ClearCapturedScreenshot();
	bool IsScreenshotCaptured() const;
public:
	static FString GetScreenshotFilePath();
};
