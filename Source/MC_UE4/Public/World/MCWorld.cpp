// Fill out your copyright notice in the Description page of Project Settings.


#include "MCWorld.h"

MCWorld::MCWorld()
{
	m_server = NewObject<UServerWrapper>();
}

MCWorld::~MCWorld()
{
}
