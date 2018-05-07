﻿#pragma once

#include "CoreMinimal.h"
#include "EGSnsService.h"

/**
 * SnsService common interface
 */
class IEGSnsService
{
public:
	virtual void Initialize() = 0;
	virtual void Finalize() = 0;

	virtual void ShareText(const FString& Text) = 0;
	virtual void ShareImageFile(const FString& Text, const FString& ImageFilePath) = 0;
};