// Fill out your copyright notice in the Description page of Project Settings.

#include "EGSnsGameModeBase.h"
#include "EGUtil.h"
#include "EGSnsUtil.h"

namespace
{
	FAutoConsoleCommand SnsInitialize(
		TEXT("EG.SNS.Init"),
		TEXT("SNS Initialize"),
		FConsoleCommandDelegate::CreateLambda([] {
			FEGSnsUtil::Initialize();
		})
	);

	FAutoConsoleCommand SnsFinalize(
		TEXT("EG.SNS.Fin"),
		TEXT("SNS Finalize"),
		FConsoleCommandDelegate::CreateLambda([] {
			FEGSnsUtil::Finalize();
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
				: TEXT("Test share text. #Test https://www.google.com");

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
				: TEXT("Test share image file. #Test https://www.google.com");

			const FString ImageFilePath = (Args.IsValidIndex(2))
				? Args[2]
				: TEXT("");

			FEGSnsUtil::ShareImageFile(ServiceType, Text, ImageFilePath);
		})
	);
}