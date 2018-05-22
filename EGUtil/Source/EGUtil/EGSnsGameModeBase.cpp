// Fill out your copyright notice in the Description page of Project Settings.

#include "EGSnsGameModeBase.h"
#include "EGUtil.h"
#include "EGSnsUtil.h"

void AEGSnsGameModeBase::InitializeSns()
{
	FEGSnsUtil::Initialize();

	OnLoggedInHandle = FEGSnsUtil::OnLoggedIn().AddUObject(this, &AEGSnsGameModeBase::OnLoggedIn);
	OnSharedHandle = FEGSnsUtil::OnShared().AddUObject(this, &AEGSnsGameModeBase::OnShared);
}

void AEGSnsGameModeBase::FinalizeSns()
{
	FEGSnsUtil::OnShared().Remove(OnSharedHandle);
	OnSharedHandle.Reset();

	FEGSnsUtil::OnLoggedIn().Remove(OnLoggedInHandle);
	OnLoggedInHandle.Reset();

	FEGSnsUtil::Finalize();
}

void AEGSnsGameModeBase::OnLoggedIn(EEGSnsServiceType ServiceType, bool bSuccess)
{
	UE_LOG(EGLog, Log, TEXT("AEGSnsGameModeBase::OnLoggedIn()"));
	UE_LOG(EGLog, Log, TEXT("ServiceType: %d"), (int32)ServiceType);
	UE_LOG(EGLog, Log, TEXT("bSuccess: %d"), (int32)bSuccess);
}

void AEGSnsGameModeBase::OnShared(EEGSnsServiceType ServiceType, bool bSuccess, const FString& ErrorMessage)
{
	UE_LOG(EGLog, Log, TEXT("AEGSnsGameModeBase::OnShared()"));
	UE_LOG(EGLog, Log, TEXT("ServiceType: %d"), (int32)ServiceType);
	UE_LOG(EGLog, Log, TEXT("bSuccess: %d"), (int32)bSuccess);
	UE_LOG(EGLog, Log, TEXT("ErrorMessage: %s"), *ErrorMessage);
}

namespace
{
	FAutoConsoleCommandWithWorld SnsInitialize(
		TEXT("EG.SNS.Init"),
		TEXT("SNS Initialize"),
		FConsoleCommandWithWorldDelegate::CreateLambda([](UWorld* World) {
			auto GameMode = World->GetAuthGameMode<AEGSnsGameModeBase>();
			if (!GameMode)
			{
				UE_LOG(EGLog, Log, TEXT("not SnsGameMode"));
				return;
			}

			GameMode->InitializeSns();
		})
	);

	FAutoConsoleCommandWithWorld SnsFinalize(
		TEXT("EG.SNS.Fin"),
		TEXT("SNS Finalize"),
		FConsoleCommandWithWorldDelegate::CreateLambda([](UWorld* World) {
			auto GameMode = World->GetAuthGameMode<AEGSnsGameModeBase>();
			if (!GameMode)
			{
				UE_LOG(EGLog, Log, TEXT("not SnsGameMode"));
			}
			GameMode->FinalizeSns();
		})
	);

	FAutoConsoleCommand SnsLogin(
		TEXT("EG.SNS.Login"),
		TEXT("(int)ServiceType"),
		FConsoleCommandWithArgsDelegate::CreateLambda([](const TArray<FString>& Args) {
			const EEGSnsServiceType ServiceType = (Args.IsValidIndex(0))
				? (EEGSnsServiceType)FCString::Atoi(*Args[0])
				: (EEGSnsServiceType)0;

			FEGSnsUtil::Login(ServiceType);
		})
	);

	FAutoConsoleCommand SnsLogout(
		TEXT("EG.SNS.Logout"),
		TEXT("(int)ServiceType"),
		FConsoleCommandWithArgsDelegate::CreateLambda([](const TArray<FString>& Args) {
			const EEGSnsServiceType ServiceType = (Args.IsValidIndex(0))
				? (EEGSnsServiceType)FCString::Atoi(*Args[0])
				: (EEGSnsServiceType)0;

			FEGSnsUtil::Logout(ServiceType);
		})
	);

	FAutoConsoleCommand SnsIsLoggedIn(
		TEXT("EG.SNS.Loggedin"),
		TEXT("(int)ServiceType"),
		FConsoleCommandWithArgsDelegate::CreateLambda([](const TArray<FString>& Args) {
			const EEGSnsServiceType ServiceType = (Args.IsValidIndex(0))
				? (EEGSnsServiceType)FCString::Atoi(*Args[0])
				: (EEGSnsServiceType)0;

			const bool isLoggedIn = FEGSnsUtil::IsLoggedIn(ServiceType);
			UE_LOG(EGLog, Log, TEXT("IsLoggedIn: %d"), (int32)isLoggedIn);
		})
	);

	FAutoConsoleCommand SnsShareText(
		TEXT("EG.SNS.Text"),
		TEXT("(int)ServiceType, (str)Text"),
		FConsoleCommandWithArgsDelegate::CreateLambda([](const TArray<FString>& Args) {
			const EEGSnsServiceType ServiceType = (Args.IsValidIndex(0))
				? (EEGSnsServiceType)FCString::Atoi(*Args[0])
				: (EEGSnsServiceType)0;

			const FString Text = (Args.IsValidIndex(1))
				? Args[1]
				: FString::Printf(TEXT("Test share text. %s #Test https://www.google.com")
					, *FDateTime::Now().ToString(TEXT("%Y/%m/%d %H:%M:%S")));

			FEGSnsUtil::ShareText(ServiceType, Text);
		})
	);

	FAutoConsoleCommand ShareImageFile(
		TEXT("EG.SNS.Image"),
		TEXT("(int)ServiceType, (str)Text, (str)ImageFilePath"),
		FConsoleCommandWithArgsDelegate::CreateLambda([](const TArray<FString>& Args) {
			const EEGSnsServiceType ServiceType = (Args.IsValidIndex(0))
				? (EEGSnsServiceType)FCString::Atoi(*Args[0])
				: (EEGSnsServiceType)0;

			const FString Text = (Args.IsValidIndex(1))
				? Args[1]
				: FString::Printf(TEXT("Test share image file. %s #Test https://www.google.com")
					, *FDateTime::Now().ToString(TEXT("%Y/%m/%d %H:%M:%S")));

			const FString ImageFilePath = (Args.IsValidIndex(2))
				? Args[2]
				: TEXT("");

			FEGSnsUtil::ShareImageFile(ServiceType, Text, ImageFilePath);
		})
	);
}