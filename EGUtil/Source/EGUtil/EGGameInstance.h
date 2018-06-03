// Copyright 2018 EG Factory. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class EGUTIL_API UEGGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class UEGScreenshotManager* ScreenshotManager;

public:
	UEGGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;
	virtual void Shutdown() override;

	class UEGScreenshotManager* GetScreenshotManager();
};