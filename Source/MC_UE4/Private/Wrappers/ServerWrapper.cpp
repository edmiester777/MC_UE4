// Fill out your copyright notice in the Description page of Project Settings.


#include "Wrappers/ServerWrapper.h"
#include <Wrappers/JVMThreadLock.h>

UServerWrapper::UServerWrapper()
{
	FString serverRoot = FPaths::ProjectIntermediateDir();
	serverRoot = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*serverRoot);
	jstring jserverRoot = JNI_ENV->NewString((jchar*)TCHAR_TO_ANSI(*serverRoot), serverRoot.Len());
	jclass jSimpleServerCls = JNI_GET_CLASS("ue/test/SimpleServer");
	JNI_CALL_STATIC_VOID_METHOD(
		jSimpleServerCls,
		JNI_GET_STATIC_METHOD(jSimpleServerCls, "main", "(Ljava/lang/String;)V"),
		jserverRoot
	);


	if (JavaTestUtil::Instance()->HasError())
	{
		FString stack = JavaTestUtil::Instance()->DescribeError();
		UE_LOG(LogTemp, Fatal, TEXT("Failed to start backend server: %s"), *stack);
	}
}

UServerWrapper::~UServerWrapper()
{
}
