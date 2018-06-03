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
	 * ĸ�� ��û
	 * ��û �����ӿ� �ٷ� �Ϸ���� ����. �Ϸ� �� OnCaptured ȣ��
	 * ĸ�� ������ ���������� ȣ�� ���� ȣ���ڰ� üũ�ؾ� ��
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