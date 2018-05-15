#pragma once

#include "CoreMinimal.h"
#include "EGSnsService.h"
#include "Android/AndroidJava.h"

/**
 * Android Twitter service
 */
class FEGSnsAndroidTwitter : public FJavaClassObject, public IEGSnsService
{
public:
	FEGSnsAndroidTwitter();
	virtual ~FEGSnsAndroidTwitter() = default;

	virtual void Initialize() override;
	virtual void Finalize() override;

	virtual void Login() override;
	virtual void Logout() override;
	virtual bool IsLoggedIn() override;

	virtual void ShareText(const FString& Text) override;
	virtual void ShareImageFile(const FString& Text, const FString& ImageFilePath) override;

private:
	static FName GetClassName();

	FJavaClassMethod InitializeMethod;
	FJavaClassMethod FinalizeMethod;
	FJavaClassMethod LoginMethod;
	FJavaClassMethod LogoutMethod;
	FJavaClassMethod IsLoggedInMethod;
	FJavaClassMethod ShareTextMethod;
	FJavaClassMethod ShareImageFileMethod;
};