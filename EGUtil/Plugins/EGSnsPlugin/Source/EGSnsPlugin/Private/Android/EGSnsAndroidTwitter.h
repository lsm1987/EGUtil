#pragma once

#include "CoreMinimal.h"
#include "EGSnsService.h"

/**
 * Android Twitter service
 */
class FEGSnsAndroidTwitter : public IEGSnsService
{
public:
	virtual ~FEGSnsAndroidTwitter() = default;

	virtual void Initialize() override;
	virtual void Finalize() override;

	virtual void Login() override;
	virtual bool IsLoggedIn() override;
	virtual void Logout() override;

	virtual void ShareText(const FString& Text) override;
	virtual void ShareImageFile(const FString& Text, const FString& ImageFilePath) override;
};