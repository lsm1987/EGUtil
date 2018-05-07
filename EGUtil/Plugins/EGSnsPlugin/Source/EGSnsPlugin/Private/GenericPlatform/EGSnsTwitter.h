#pragma once

#include "CoreMinimal.h"
#include "EGSnsService.h"

/**
 * Generic platform Twitter service
 */
class FEGSnsGenericTwitter : public IEGSnsService
{
public:
	virtual void Initialize() override;
	virtual void Finalize() override;

	virtual void ShareText(const FString& Text) override;
	virtual void ShareImageFile(const FString& Text, const FString& ImageFilePath) override;
};

typedef FEGSnsGenericTwitter FEGSnsTwitter;