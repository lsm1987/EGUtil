#include "EGSnsUtil.h"
#include "EGSnsPluginRuntimeSettings.h"

#include "EGSnsTwitter.h"

TMap<EEGSnsServiceType, TSharedPtr<IEGSnsService>> FEGSnsUtil::Services;

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