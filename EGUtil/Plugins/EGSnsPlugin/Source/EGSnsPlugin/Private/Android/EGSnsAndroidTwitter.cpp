#include "EGSnsAndroidTwitter.h"
#include "EGSnsPlugin.h"
#include "EGSnsPluginRuntimeSettings.h"
#include "EGSnsUtil.h"

FEGSnsAndroidTwitter::FEGSnsAndroidTwitter()
	: FJavaClassObject(GetClassName(), "()V")
	, InitializeMethod(GetClassMethod("AndroidThunkJava_Initialize", "(Ljava/lang/String;Ljava/lang/String;)V"))
	, FinalizeMethod(GetClassMethod("AndroidThunkJava_Finalize", "()V"))
	, LoginMethod(GetClassMethod("AndroidThunkJava_Login", "()V"))
	, LogoutMethod(GetClassMethod("AndroidThunkJava_Logout", "()V"))
	, IsLoggedInMethod(GetClassMethod("AndroidThunkJava_IsLoggedIn", "()Z"))
	, ShareTextMethod(GetClassMethod("AndroidThunkJava_ShareText", "(Ljava/lang/String;)V"))
	, ShareImageFileMethod(GetClassMethod("AndroidThunkJava_ShareImageFile", "(Ljava/lang/String;Ljava/lang/String;)V"))
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

	CallMethod<void>(FinalizeMethod);
}

void FEGSnsAndroidTwitter::Login()
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsAndroidTwitter::Login()"));

	CallMethod<void>(LoginMethod);
}

void FEGSnsAndroidTwitter::Logout()
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsAndroidTwitter::Logout()"));

	CallMethod<void>(LogoutMethod);
}

bool FEGSnsAndroidTwitter::IsLoggedIn()
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsAndroidTwitter::IsLoggedIn()"));
	
	return CallMethod<bool>(IsLoggedInMethod);
}

void FEGSnsAndroidTwitter::ShareText(const FString& Text)
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsAndroidTwitter::ShareText()"));
	UE_LOG(EGSnsLog, Log, TEXT("Text: %s"), *Text);

	CallMethod<void>(ShareTextMethod, GetJString(Text));
}

void FEGSnsAndroidTwitter::ShareImageFile(const FString& Text, const FString& ImageFilePath)
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsAndroidTwitter::ShareImageFile()"));
	UE_LOG(EGSnsLog, Log, TEXT("Text: %s"), *Text);
	UE_LOG(EGSnsLog, Log, TEXT("ImageFilePath: %s"), *ImageFilePath);
	
	CallMethod<void>(ShareImageFileMethod, GetJString(Text), GetJString(ImageFilePath));
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

JNI_METHOD void Java_com_lsm1987_egsnsplugin_EGSnsTwitter_nativeOnLoggedIn(JNIEnv* jenv, jobject thiz, jboolean bSuccess)
{
	UE_LOG(EGSnsLog, Log, TEXT("EGSnsTwitter_nativeOnLoggedIn()"));
	UE_LOG(EGSnsLog, Log, TEXT("bSuccess: %d"), (bSuccess == JNI_TRUE) ? 1 : 0);

	FEGSnsUtil::OnLoggedIn.Broadcast(EEGSnsServiceType::Twitter, bSuccess);
}