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
     * If an error has occurred during prior execution,
     * return a formatted message to describe the exception.
     * 
     * This will also clear the existing exception.
     * 
     * @see JavaTestUtil::HasError()
     * @seealso http://journals.ecs.soton.ac.uk/java/tutorial/native1.1/implementing/error.html
     */
    FString DescribeError();

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