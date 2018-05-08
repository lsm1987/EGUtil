#pragma once

#include "CoreMinimal.h"

/**
 * SnsService common interface
 */
class IEGSnsService
{
public:
	virtual ~IEGSnsService() = 0;

	virtual void Initialize() = 0;
	virtual void Finalize() = 0;

	virtual void Login() = 0;
	virtual bool IsLoggedIn() = 0;
	virtual void Logout() = 0;

	virtual void ShareText(const FString& Text) = 0;
	virtual void ShareImageFile(const FString& Text, const FString& ImageFilePath) = 0;
};