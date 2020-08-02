// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "World/MCWorld.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MC_UE4GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MC_UE4_API AMC_UE4GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	TSharedPtr<MCWorld> world = nullptr;
public:
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
};
