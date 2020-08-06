#include "JavaTestUtil.h"

JavaTestUtil* JavaTestUtil::instance()
{
    static JavaTestUtil* instance = nullptr;

    if (instance == nullptr)
        instance = new JavaTestUtil();

    return instance;
}

JavaTestUtil::JavaTestUtil()
{
    m_jvm = nullptr;
    m_env = nullptr;
    InitJVM();
}

JavaTestUtil::~JavaTestUtil()
{
    DestroyJVM();
}

JNIEnv* JavaTestUtil::GetEnv()
{
    return m_env;
}

FString JavaTestUtil::GetMCPClasspath()
{
    FString projectDir = FPaths::ProjectDir();
    FString classpath = FPaths::Combine(
        projectDir,
        "third-party",
        "mcp-reborn",
        "build",
        "classes",
        "java",
        "main"
    );
    return classpath;
}

void JavaTestUtil::InitJVM()
{
    if(m_jvm == nullptr)
    {
        FString cpOpt = "-Djava.class.path=" + GetMCPClasspath();
        JavaVMInitArgs vmArgs;
        JavaVMOption vmOptions[3];
        vmOptions[0].optionString = TCHAR_TO_ANSI(*cpOpt);
        vmOptions[1].optionString = "-Xms1m";
        vmOptions[2].optionString = "-Xmx1g";
        vmArgs.version = JNI_VERSION_1_8;
        vmArgs.nOptions = 1;
        vmArgs.options = vmOptions;
        vmArgs.ignoreUnrecognized = true;

        jint createStatus = JNI_CreateJavaVM(&m_jvm, (void**)&m_env, &vmArgs);
        
        // checking status
        if(createStatus != JNI_OK)
        {
            m_jvm = nullptr;
            m_env = nullptr;
            UE_LOG(LogTemp, Error, TEXT("Failed to initialize JVM."));
            return;
        }

        FString loadedMessage = "JVM Loaded. Version: ";
        jint ver = m_env->GetVersion();
        loadedMessage += FString::FromInt((int)((ver >> 16) & 0x0f));
        loadedMessage += ".";
        loadedMessage += FString::FromInt((int)(ver & 0x0f));
        UE_LOG(LogTemp, Display, TEXT("%s"), *loadedMessage);
    }
}

void JavaTestUtil::DestroyJVM()
{
    if(m_jvm != nullptr)
    {
        m_jvm->DestroyJavaVM();
        m_jvm = nullptr;
        m_env = nullptr;
    }
}
