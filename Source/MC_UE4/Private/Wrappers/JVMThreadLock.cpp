// Fill out your copyright notice in the Description page of Project Settings.


#include "Wrappers/JVMThreadLock.h"
#include <TestUtil/JavaTestUtil.h>

JVMThreadLock::JVMThreadLock()
{
	JavaTestUtil::Instance()->AttachThread();
}

JVMThreadLock::~JVMThreadLock()
{
	JavaTestUtil::Instance()->DetachThread();
}
