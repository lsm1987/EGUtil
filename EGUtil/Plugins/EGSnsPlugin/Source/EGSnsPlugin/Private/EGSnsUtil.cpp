#include "EGSnsUtil.h"
#include "EGSnsPluginRuntimeSettings.h"

#include "EGSnsTwitter.h"

TMap<EEGSnsServiceType, TSharedPtr<IEGSnsService>> FEGSnsUtil::Services;

void FEGSnsUtil::Initialize()
{
	UE_LOG(EGSnsLog, Log, TEXT("FEGSnsUtil::Initialize()"));

	if (GetDefault<UEGSnsPluginRuntimeSettings>()->IsTwitterEnable())
	{
		TSharedPtr<FEGSnsTwitter> Service(new FEGSnsTwitter());
		Service->Initialize();
		Services.Add(EEGSnsServiceType::Twitter, Service);
	}
}