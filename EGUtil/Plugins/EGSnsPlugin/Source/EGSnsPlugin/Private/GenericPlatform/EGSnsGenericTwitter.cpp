#include "EGSnsGenericTwitter.h"
#include "EGSnsPlugin.h"
#include "EGSnsPluginRuntimeSettings.h"

void FEGSnsGenericTwitter::Initialize()
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsGenericTwitter::Initialize()"));
	UE_LOG(EGSnsLog, Log, TEXT("CustomerKey: %s"), *GetDefault<UEGSnsPluginRuntimeSettings>()->GetTwitterConsumerKey());
	UE_LOG(EGSnsLog, Log, TEXT("CustomerSecret: %s"), *GetDefault<UEGSnsPluginRuntimeSettings>()->GetTwitterConsumerSecret());
}

void FEGSnsGenericTwitter::Finalize()
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsGenericTwitter::Finalize()"));
}

void FEGSnsGenericTwitter::Login()
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsGenericTwitter::Login()"));
}

bool FEGSnsGenericTwitter::IsLoggedIn()
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsGenericTwitter::IsLoggedIn()"));
	return false;
}

void FEGSnsGenericTwitter::Logout()
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsGenericTwitter::Logout()"));
}

void FEGSnsGenericTwitter::ShareText(const FString& Text)
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsGenericTwitter::ShareText()"));
	UE_LOG(EGSnsLog, Log, TEXT("Text: %s"), *Text);
}

void FEGSnsGenericTwitter::ShareImageFile(const FString& Text, const FString& ImageFilePath)
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsGenericTwitter::ShareImageFile()"));
	UE_LOG(EGSnsLog, Log, TEXT("Text: %s"), *Text);
	UE_LOG(EGSnsLog, Log, TEXT("ImageFilePath: %s"), *ImageFilePath);
}