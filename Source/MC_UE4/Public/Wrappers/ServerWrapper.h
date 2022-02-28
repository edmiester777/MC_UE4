// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <TestUtil/JavaTestUtil.h>
#include "UObject/NoExportTypes.h"
#include "ServerWrapper.generated.h"

/**
 * Wrapper around 
 */
UCLASS()
class MC_UE4_API UServerWrapper : public UObject
{
	GENERATED_BODY()
public:
	UServerWrapper();
	virtual ~UServerWrapper() override;

private:
	jobject m_dedicatedServer;
};
