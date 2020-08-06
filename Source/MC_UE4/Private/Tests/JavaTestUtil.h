#pragma once


#include "CoreMinimal.h"
#include <jni.h>

/**
 * This class is a utility class for interfacing with JVM and minecraft source
 * files from unreal code.
 */
class JavaTestUtil {
private:
    JavaVM* m_jvm;
    JNIEnv* m_env;

public:
    static JavaTestUtil* instance();
    JavaTestUtil();
    ~JavaTestUtil();
    JNIEnv* GetEnv();

private:
    static FString GetMCPClasspath();
    void InitJVM();
    void DestroyJVM();
};