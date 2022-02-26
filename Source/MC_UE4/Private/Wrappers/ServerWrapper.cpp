// Fill out your copyright notice in the Description page of Project Settings.


#include "Wrappers/ServerWrapper.h"
#include <Wrappers/JVMThreadLock.h>

UServerWrapper::UServerWrapper()
{
	JNI_ENV;
	Bootstrap();
}

UServerWrapper::~UServerWrapper()
{
}

void UServerWrapper::Bootstrap()
{
	FString e = JavaTestUtil::Instance()->DescribeError();
	JVMThreadLock lock;
	jclass tst = JNI_GET_CLASS("java/util/Random");
	jclass jBootstrapCls = JNI_GET_CLASS("net/minecraft/server/Bootstrap");
	FString err = JavaTestUtil::Instance()->DescribeError();
	jmethodID bootstrapMethod = JNI_GET_STATIC_METHOD(jBootstrapCls, "bootStrap", "()V");
	JNI_CALL_STATIC_VOID_METHOD(jBootstrapCls, bootstrapMethod);
}
