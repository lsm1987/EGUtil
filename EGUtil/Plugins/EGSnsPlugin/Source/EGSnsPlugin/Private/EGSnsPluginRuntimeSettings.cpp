#include "EGSnsPluginRuntimeSettings.h"

//////////////////////////////////////////////////////////////////////////
// UEGSnsPluginRuntimeSettings

UEGSnsPluginRuntimeSettings::UEGSnsPluginRuntimeSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bTwitterEnable(true)
{
}

bool UEGSnsPluginRuntimeSettings::IsTwitterEnable() const
{
	return bTwitterEnable;
}

FString UEGSnsPluginRuntimeSettings::GetTwitterConsumerKey() const
{
	return TwitterConsumerKey;
}

FString UEGSnsPluginRuntimeSettings::GetTwitterConsumerSecret() const
{
	return TwitterConsumerSecret;
}