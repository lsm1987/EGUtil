#include "EGSnsTwitter.h"
#include "EGSnsPluginRuntimeSettings.h"

void FEGSnsGenericTwitter::Initialize()
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsGenericTwitter::Initialize()"));
	UE_LOG(EGSnsLog, Log, TEXT("CustomerKey: %s"), *GetDefault<UEGSnsPluginRuntimeSettings>()->GetTwitterConsumerKey());
	UE_LOG(EGSnsLog, Log, TEXT("CustomerSecret: %s"), *GetDefault<UEGSnsPluginRuntimeSettings>()->GetTwitterConsumerSecret());
}

void FEGSnsGenericTwitter::Finalize()
{
}

void FEGSnsGenericTwitter::ShareText(const FString& Text)
{
}

void FEGSnsGenericTwitter::ShareImageFile(const FString& Text, const FString& ImageFilePath)
{
}