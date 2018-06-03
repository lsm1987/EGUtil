// Copyright 2018 EG Factory. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EGScreenshotManager.generated.h"

/**
 * 
 */
UCLASS()
class EGUTIL_API UEGScreenshotManager : public UObject
{
	GENERATED_BODY()
	
private:
	FDelegateHandle OnCapturedHandle;
	TFunction<void()> OnCapturedCallback;
	int32 CapturedWidth;
	int32 CapturedHeight;
	TArray<FColor> CapturedColors;
	
public:
	UEGScreenshotManager();

	static UEGScreenshotManager* Get(class UWorld* World);
	bool CanRequestCapture() const;
	
	/**
	 * 캡쳐 요청
	 * 요청 프레임에 바로 완료되지 않음. 완료 시 OnCaptured 호출
	 * 캡쳐 가능한 상태인지는 호출 전에 호출자가 체크해야 함
	 */
	void RequestCapture(TFunction<void()> OnCapturedCallback);
	void RequestCapture();
private:
	void OnCaptured(int32 Width, int32 Height, const TArray<FColor>& Colors);
	void ClearCaptured();
	bool IsCaptured() const;
public:
	bool SaveCapturedToFile(const FString& Path);
};