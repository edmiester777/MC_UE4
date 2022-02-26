// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Wrappers/ServerWrapper.h"

/**
 * 
 */
class MC_UE4_API MCWorld
{
public:
	MCWorld();
	~MCWorld();

private:
	UServerWrapper* m_server;
};
