#include "EGSnsAndroidTwitter.h"
#include "EGSnsPlugin.h"
#include "EGSnsPluginRuntimeSettings.h"

FEGSnsAndroidTwitter::FEGSnsAndroidTwitter()
	: FJavaClassObject(GetClassName(), "()V")
	, InitializeMethod(GetClassMethod("AndroidThunkJava_Initialize", "(Ljava/lang/String;Ljava/lang/String;)V"))
	, LoginMethod(GetClassMethod("AndroidThunkJava_Login", "()V"))
{
}

void FEGSnsAndroidTwitter::Initialize()
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsAndroidTwitter::Initialize()"));

	const FString ConsumerKey = GetDefault<UEGSnsPluginRuntimeSettings>()->GetTwitterConsumerKey();
	const FString ConsumerSecret = GetDefault<UEGSnsPluginRuntimeSettings>()->GetTwitterConsumerSecret();

	UE_LOG(EGSnsLog, Log, TEXT("CustomerKey: %s"), *ConsumerKey);
	UE_LOG(EGSnsLog, Log, TEXT("CustomerSecret: %s"), *ConsumerSecret);

	CallMethod<void>(InitializeMethod, GetJString(ConsumerKey), GetJString(ConsumerSecret));
}

void FEGSnsAndroidTwitter::Finalize()
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsAndroidTwitter::Finalize()"));
}

void FEGSnsAndroidTwitter::Login()
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsAndroidTwitter::Login()"));

	CallMethod<void>(LoginMethod);
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

FName FEGSnsAndroidTwitter::GetClassName()
{
	if (FAndroidMisc::GetAndroidBuildVersion() >= 1)
	{
		return FName("com/lsm1987/egsnsplugin/EGSnsTwitter");
	}
	else
	{
		return FName("");
	}
}