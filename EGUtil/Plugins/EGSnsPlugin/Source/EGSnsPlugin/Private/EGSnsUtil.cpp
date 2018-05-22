#include "EGSnsUtil.h"
#include "EGSnsPlugin.h"
#include "EGSnsPluginRuntimeSettings.h"

#if PLATFORM_ANDROID
#include "Android/EGSnsAndroidTwitter.h"
typedef FEGSnsAndroidTwitter FEGSnsTwitter;
#else
#include "GenericPlatform/EGSnsGenericTwitter.h"
typedef FEGSnsGenericTwitter FEGSnsTwitter;
#endif

TMap<EEGSnsServiceType, TSharedPtr<IEGSnsService>> FEGSnsUtil::Services;

FEGSnsUtil::FOnLoggedIn FEGSnsUtil::OnLoggedInDelegate;
FEGSnsUtil::FOnShared FEGSnsUtil::OnSharedDelegate;

void FEGSnsUtil::Initialize()
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsUtil::Initialize()"));

	InitializeService(EEGSnsServiceType::Twitter);
}

void FEGSnsUtil::Finalize()
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsUtil::Finalize()"));

	FinalizeService(EEGSnsServiceType::Twitter);
}

void FEGSnsUtil::Login(EEGSnsServiceType ServiceType)
{
	auto Service = FindService(ServiceType);
	if (Service.IsValid())
	{
		Service->Login();
	}
}

bool FEGSnsUtil::IsLoggedIn(EEGSnsServiceType ServiceType)
{
	auto Service = FindService(ServiceType);
	if (Service.IsValid())
	{
		return Service->IsLoggedIn();
	}

	return false;
}

void FEGSnsUtil::Logout(EEGSnsServiceType ServiceType)
{
	auto Service = FindService(ServiceType);
	if (Service.IsValid())
	{
		Service->Logout();
	}
}

void FEGSnsUtil::ShareText(EEGSnsServiceType ServiceType, const FString& Text)
{
	auto Service = FindService(ServiceType);
	if (Service.IsValid())
	{
		Service->ShareText(Text);
	}
}

void FEGSnsUtil::ShareImageFile(EEGSnsServiceType ServiceType, const FString& Text, const FString& ImageFilePath)
{
	auto Service = FindService(ServiceType);
	if (Service.IsValid())
	{
		Service->ShareImageFile(Text, ImageFilePath);
	}
}

FEGSnsUtil::FOnLoggedIn& FEGSnsUtil::OnLoggedIn()
{
	return OnLoggedInDelegate;
}

FEGSnsUtil::FOnShared& FEGSnsUtil::OnShared()
{
	return OnSharedDelegate;
}

TSharedPtr<IEGSnsService> FEGSnsUtil::FindService(EEGSnsServiceType ServiceType)
{
	TSharedPtr<IEGSnsService>* Service = Services.Find(ServiceType);
	return (Service != nullptr) ? *Service : nullptr;
}

bool FEGSnsUtil::IsServiceEnabled(EEGSnsServiceType ServiceType)
{
	switch (ServiceType)
	{
	case EEGSnsServiceType::Twitter:
		return GetDefault<UEGSnsPluginRuntimeSettings>()->IsTwitterEnable();
	default:
		UE_LOG(EGSnsLog, Error, TEXT("Cannot find service enable setting. ServiceType: %d"), (int32)ServiceType);
		return false;
	}
}

void FEGSnsUtil::InitializeService(EEGSnsServiceType ServiceType)
{
	if (!IsServiceEnabled(ServiceType))
	{
		return;
	}

	TSharedPtr<IEGSnsService> Service;

	switch (ServiceType)
	{
	case EEGSnsServiceType::Twitter:
		Service = TSharedPtr<IEGSnsService>(new FEGSnsTwitter());
	}

	if (!Service.IsValid())
	{
		UE_LOG(EGSnsLog, Error, TEXT("Cannot create service. ServiceType: %d"), (int32)ServiceType);
		return;
	}

	Service->Initialize();
	Services.Add(ServiceType, Service);
}

void FEGSnsUtil::FinalizeService(EEGSnsServiceType ServiceType)
{
	TSharedPtr<IEGSnsService> Service = FindService(ServiceType);
	if (Service.IsValid())
	{
		Service->Finalize();
	}
	Services.Remove(ServiceType);
}