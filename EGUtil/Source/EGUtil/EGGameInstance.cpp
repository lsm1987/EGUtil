// Copyright 2018 EG Factory. All Rights Reserved.

#include "EGGameInstance.h"
#include "EGScreenshotManager.h"

UEGGameInstance::UEGGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ScreenshotManager(nullptr)
{
}

void UEGGameInstance::Init()
{
	Super::Init();

	ScreenshotManager = NewObject<UEGScreenshotManager>(this);
}

void UEGGameInstance::Shutdown()
{
	Super::Shutdown();

	ScreenshotManager = nullptr;
}

UEGScreenshotManager* UEGGameInstance::GetScreenshotManager()
{
	return ScreenshotManager;
}