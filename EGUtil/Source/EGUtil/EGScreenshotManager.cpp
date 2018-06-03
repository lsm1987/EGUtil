// Copyright 2018 EG Factory. All Rights Reserved.

#include "EGScreenshotManager.h"
#include "EGUtil.h"
#include "EGGameInstance.h"
#include "Engine/GameViewportClient.h"
#include "Engine/World.h"
#include "ImageUtils.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

UEGScreenshotManager::UEGScreenshotManager()
	: Super()
	, CapturedWidth(0)
	, CapturedHeight(0)
{
}

UEGScreenshotManager* UEGScreenshotManager::Get(UWorld* World)
{
	if (World)
	{
		auto GameInstance = World->GetGameInstance<UEGGameInstance>();
		if (GameInstance)
		{
			return GameInstance->GetScreenshotManager();
		}
	}

	UE_LOG(EGLog, Log, TEXT("ScreenshotManager == nullptr"));
	return nullptr;
}

bool UEGScreenshotManager::CanRequestCapture() const
{
	return (!OnCapturedHandle.IsValid()
		&& !OnCapturedCallback);
}

void UEGScreenshotManager::RequestCapture(TFunction<void()> OnCapturedCallback)
{
	check(CanRequestCapture());

	ClearCaptured();
	OnCapturedHandle = UGameViewportClient::OnScreenshotCaptured().AddUObject(this, &UEGScreenshotManager::OnCaptured);
	this->OnCapturedCallback = OnCapturedCallback;

	FScreenshotRequest::RequestScreenshot(true);
}

void UEGScreenshotManager::RequestCapture()
{
	RequestCapture(nullptr);
}

void UEGScreenshotManager::OnCaptured(int32 Width, int32 Height, const TArray<FColor>& Colors)
{
	UE_LOG(EGLog, Log, TEXT("OnCaptured. Width: %d, Height: %d"), Width, Height);

	OnCapturedHandle.Reset();

	CapturedWidth = Width;
	CapturedHeight = Height;
	CapturedColors = Colors;

	if (OnCapturedCallback)
	{
		OnCapturedCallback();
		OnCapturedCallback = nullptr;
	}
}

void UEGScreenshotManager::ClearCaptured()
{
	CapturedWidth = 0;
	CapturedHeight = 0;
	CapturedColors.Reset();
}

bool UEGScreenshotManager::IsCaptured() const
{
	return (CapturedWidth != 0
		&& CapturedHeight != 0
		&& CapturedColors.Num() != 0);
}

bool UEGScreenshotManager::SaveCapturedToFile(const FString& Path)
{
	if (!IsCaptured())
	{
		UE_LOG(EGLog, Log, TEXT("Screenshot not captured"));
		return false;
	}

	TArray<uint8> CompressedBitmap;
	FImageUtils::CompressImageArray(CapturedWidth, CapturedHeight, CapturedColors, CompressedBitmap);
	const bool bResult = FFileHelper::SaveArrayToFile(CompressedBitmap, *Path);

	UE_LOG(EGLog, Log, TEXT("Screenshot file saved. path: %s, absPath: %s"), *Path, *FPaths::ConvertRelativePathToFull(Path));

	return bResult;
}

namespace
{
	FAutoConsoleCommandWithWorldAndArgs ScreenCapture(
		TEXT("EG.Screen.Capture"),
		TEXT("Capture screenshot to memory. (bool)SaveToFile"),
		FConsoleCommandWithWorldAndArgsDelegate::CreateLambda([](const TArray<FString>& Args, UWorld* World) {
			auto ScreenshotManager = UEGScreenshotManager::Get(World);
			if (!ScreenshotManager)
			{
				return;
			}

			const bool bSaveToFile = (Args.IsValidIndex(0))
				? FCString::Atoi(*Args[0]) != 0
				: false;

			if (bSaveToFile)
			{
				ScreenshotManager->RequestCapture([ScreenshotManager] {
					const FString FilePath = FPaths::Combine(
						FPaths::ProjectPersistentDownloadDir(), TEXT("Temp"), TEXT("ScreenshotTest.png"));

					ScreenshotManager->SaveCapturedToFile(FilePath);
				});
			}
			else
			{
				ScreenshotManager->RequestCapture();
			}
		})
	);
}