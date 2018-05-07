// Fill out your copyright notice in the Description page of Project Settings.

#include "EGSnsGameModeBase.h"
#include "EGSnsUtil.h"

namespace
{
	FAutoConsoleCommand SnsInitialize(
		TEXT("EG.SNS.Init"),
		TEXT("call sns initialize"),
		FConsoleCommandDelegate::CreateLambda([] {
			FEGSnsUtil::Initialize();
		})
	);
}