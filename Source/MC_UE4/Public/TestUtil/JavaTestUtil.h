#pragma once


#include "CoreMinimal.h"
#include <jni.h>

#define JTI_INSTANCE JavaTestUtil::Instance()
#define JNI_ENV JTI_INSTANCE->GetEnv()
#define JNI_CLEAR_ERROR JTI_INSTANCE->ClearError()
#define JNI_TEST_CHECK_AND_PRINT_ERROR \
    if (JTI_INSTANCE->HasError()) \
    { \
        FString exc = JTI_INSTANCE->DescribeError(); \
        UE_LOG(LogTemp, Error, TEXT("%s"), *exc); \
        return false; \
    }
#define JNI_GET_CLASS(cls) JNI_ENV->FindClass(cls)
#define _JNI_GET_METHOD(type, jcls, method, sig) \
    JNI_ENV->Get##type##MethodID(jcls, method, sig)
#define JNI_GET_STATIC_METHOD(jcls, method, sig) \
    _JNI_GET_METHOD(Static, jcls, method, sig)


#define _JNI_CALL_METHOD(type, cls, method, ...) \
    JNI_ENV->Call##type##Method(cls, method, __VA_ARGS__)
#define JNI_CALL_STATIC_VOID_METHOD(cls, method, ...) \
    _JNI_CALL_METHOD(StaticVoid, cls, method, __VA_ARGS__)

#define _JNI_GET_FIELD_ID(type, cls, name, sig) \
    JNI_ENV->Get##type##FieldID(cls, name, sig)
#define JNI_GET_STATIC_FIELD_ID(Static, cls, name, sig)

#define _JNI_GET_FIELD(type, cls, field) \
    JNI_ENV->Get##type##Field(cls, field)
#define JNI_GET_STATIC_OBJECT_FIELD(cls, field) \
    _JNI_GET_FIELD(StaticObject, cls, field)

/**
 * This class is a utility class for interfacing with JVM and minecraft source
 * files from unreal code.
 */
class JavaTestUtil {
private:
    JavaVM* m_jvm;
    JNIEnv* m_env;

public:
    static JavaTestUtil* Instance();
    JavaTestUtil();
    ~JavaTestUtil();
    JNIEnv* GetEnv();

    /**
     * Check if an error has occurred during prior
     * execution.
     */
    bool HasError();

    /**
     * If an error exists, clear it from the VM.
     */
    void ClearError();

    /**
     * If an error has occurred during prior execution,
     * return a formatted message to describe the exception.
     * 
     * This will also clear the existing exception.
     * 
     * @see JavaTestUtil::HasError()
     * @seealso http://journals.ecs.soton.ac.uk/java/tutorial/native1.1/implementing/error.html
     */
    FString DescribeError();

    /**
     * Attach this thread to JVM for execution.
     */
    void AttachThread();

    /**
     * Detach this thread from JVM
     */
    void DetachThread();

private:
    static FString GetMCPClasspath();
    void InitJVM();
    void DestroyJVM();

    /**
     * Recursively find all possible classpaths (from gradle) to load
     * with the JVM environment.
     * 
     * @param dir Current directory.
     * @param[out] files A list of jar files to add to classpath.
     */
    static void FindAllClasspathJars(
        FString dir,
        TArray<FString>& files
    );
};