#pragma once

#include "CoreMinimal.h"

enum class EEGSnsServiceType : int32
{
	Twitter,
};

class IEGSnsService;

class EGSNSPLUGIN_API FEGSnsUtil
{
public:
	static void Initialize();
	static void Finalize();

	static void Login(EEGSnsServiceType ServiceType);
	static bool IsLoggedIn(EEGSnsServiceType ServiceType);
	static void Logout(EEGSnsServiceType ServiceType);

	static void ShareText(EEGSnsServiceType ServiceType, const FString& Text);
	static void ShareImageFile(EEGSnsServiceType ServiceType, const FString& Text, const FString& ImageFilePath);

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLoggedIn, EEGSnsServiceType /*ServiceType*/, bool /*bSuccess*/);

	static FOnLoggedIn OnLoggedIn;

private:
	static TMap<EEGSnsServiceType, TSharedPtr<IEGSnsService>> Services;

	static TSharedPtr<IEGSnsService> FindService(EEGSnsServiceType ServiceType);
	static bool IsServiceEnabled(EEGSnsServiceType ServiceType);
	static void InitializeService(EEGSnsServiceType ServiceType);
	static void FinalizeService(EEGSnsServiceType ServiceType);
};