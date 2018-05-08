#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "Engine/DeveloperSettings.h"
#include "EGSnsPluginRuntimeSettings.generated.h"

/**
 * Implements the settings for the EGSnsPlugin.
 */
UCLASS(config=Game, defaultconfig, meta = (DisplayName = "EGSnsPlugin Settings"))
class UEGSnsPluginRuntimeSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UEGSnsPluginRuntimeSettings(const FObjectInitializer& ObjectInitializer);

private:
	// Twitter enable
	UPROPERTY(EditAnywhere, config, Category=Twitter)
	bool bTwitterEnable;

	// Twitter consumer key (API Key)
	UPROPERTY(EditAnywhere, config, Category=Twitter)
	FString TwitterConsumerKey;

	// Twitter consumer secret (API Secret)
	UPROPERTY(EditAnywhere, config, Category=Twitter)
	FString TwitterConsumerSecret;

public:
	bool IsTwitterEnable() const;
	FString GetTwitterConsumerKey() const;
	FString GetTwitterConsumerSecret() const;
};