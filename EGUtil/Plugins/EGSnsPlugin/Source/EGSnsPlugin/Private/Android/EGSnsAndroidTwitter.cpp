#include "EGSnsAndroidTwitter.h"
#include "EGSnsPlugin.h"
#include "EGSnsPluginRuntimeSettings.h"

void FEGSnsAndroidTwitter::Initialize()
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsAndroidTwitter::Initialize()"));
	UE_LOG(EGSnsLog, Log, TEXT("CustomerKey: %s"), *GetDefault<UEGSnsPluginRuntimeSettings>()->GetTwitterConsumerKey());
	UE_LOG(EGSnsLog, Log, TEXT("CustomerSecret: %s"), *GetDefault<UEGSnsPluginRuntimeSettings>()->GetTwitterConsumerSecret());
}

void FEGSnsAndroidTwitter::Finalize()
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsAndroidTwitter::Finalize()"));
}

void FEGSnsAndroidTwitter::Login()
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsAndroidTwitter::Login()"));
}

bool FEGSnsAndroidTwitter::IsLoggedIn()
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsAndroidTwitter::IsLoggedIn()"));
	return false;
}

void FEGSnsAndroidTwitter::Logout()
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsAndroidTwitter::Logout()"));
}

void FEGSnsAndroidTwitter::ShareText(const FString& Text)
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsAndroidTwitter::ShareText()"));
	UE_LOG(EGSnsLog, Log, TEXT("Text: %s"), *Text);
}

void FEGSnsAndroidTwitter::ShareImageFile(const FString& Text, const FString& ImageFilePath)
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsAndroidTwitter::ShareImageFile()"));
	UE_LOG(EGSnsLog, Log, TEXT("Text: %s"), *Text);
	UE_LOG(EGSnsLog, Log, TEXT("ImageFilePath: %s"), *ImageFilePath);
}