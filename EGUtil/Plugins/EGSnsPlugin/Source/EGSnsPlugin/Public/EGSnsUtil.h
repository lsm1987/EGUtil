#pragma once

#include "CoreMinimal.h"

enum class EEGSnsServiceType : int32
{
	Twitter,
};

class EGSNSPLUGIN_API FEGSnsUtil
{
public:
	static void Initialize();
};