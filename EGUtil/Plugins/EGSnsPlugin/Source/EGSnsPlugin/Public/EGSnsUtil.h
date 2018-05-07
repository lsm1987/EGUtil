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

private:
	static TMap<EEGSnsServiceType, TSharedPtr<IEGSnsService>> Services;

	static TSharedPtr<IEGSnsService> FindService(EEGSnsServiceType ServiceType);
	static bool IsServiceEnabled(EEGSnsServiceType ServiceType);
	static void InitializeService(EEGSnsServiceType ServiceType);
	static void FinalizeService(EEGSnsServiceType ServiceType);
};