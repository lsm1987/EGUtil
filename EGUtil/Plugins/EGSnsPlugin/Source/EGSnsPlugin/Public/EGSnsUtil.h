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

private:
	static TMap<EEGSnsServiceType, TSharedPtr<IEGSnsService>> Services;
};