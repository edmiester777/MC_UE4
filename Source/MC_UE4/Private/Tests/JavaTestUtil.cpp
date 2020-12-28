#include "JavaTestUtil.h"

JavaTestUtil* JavaTestUtil::Instance()
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

bool JavaTestUtil::HasError()
{
    return (bool)GetEnv()->ExceptionCheck();
}

void JavaTestUtil::ClearError()
{
    if (HasError())
    {
        GetEnv()->ExceptionClear();
    }
}

FString JavaTestUtil::DescribeError()
{
    if (!HasError())
        return FString();

    jthrowable exc = GetEnv()->ExceptionOccurred();
    jclass throwableCls = GetEnv()->FindClass("java/lang/Throwable");

    // StringWriter setup
    jclass stringwriterCls = GetEnv()->FindClass("java/io/StringWriter");
    jobject stringwriter = GetEnv()->NewObject(
        stringwriterCls,
        GetEnv()->GetMethodID(
            stringwriterCls,
            "<init>",
            "()V"
        )
    );

    // PrintWriter setup
    jclass printwriterCls = GetEnv()->FindClass("java/io/PrintWriter");
    jobject printwriter = GetEnv()->NewObject(
        printwriterCls,
        GetEnv()->GetMethodID(
            printwriterCls,
            "<init>",
            "(Ljava/io/Writer;)V"
        ),
        stringwriter
    );

    // Writing exception message to PrintWriter
    GetEnv()->CallVoidMethod(
        exc,
        GetEnv()->GetMethodID(
            throwableCls,
            "printStackTrace",
            "(Ljava/io/PrintWriter;)V"
        ),
        printwriter
    );

    // Getting written string
    jstring stack = (jstring)GetEnv()->CallObjectMethod(
        stringwriter,
        GetEnv()->GetMethodID(
            stringwriterCls,
            "toString",
            "()Ljava/lang/String;"
        )
    );

    // converting
    const char* cstack = GetEnv()->GetStringUTFChars(stack, NULL);
    FString fstack(UTF8_TO_TCHAR(cstack));

    // cleanup
    ClearError();
    GetEnv()->ReleaseStringUTFChars(stack, cstack);
    GetEnv()->DeleteLocalRef(printwriter);
    GetEnv()->DeleteLocalRef(stringwriter);

    return fstack;
}

FString JavaTestUtil::GetMCPClasspath()
{
    FString projectDir = FPaths::ProjectDir();
    FString fullPath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*projectDir);
    FString classpath = FPaths::Combine(
        fullPath,
        TEXT("third-party"),
        TEXT("mcp-reborn"),
        TEXT("build"),
        TEXT("classes"),
        TEXT("java"),
        TEXT("main")
    );

    // getting gradle jars
    TArray<FString> jarFiles;
    FindAllClasspathJars(
        FPaths::Combine(
            fullPath,
            TEXT("third-party"),
            TEXT("mcp-reborn"),
            TEXT("gradle_install"),
            TEXT("caches")
        ),
        jarFiles
    );

    // Checking and joining dependencies
    if (jarFiles.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("[JVM] We've detected 0 dependencies, have you bootstrapped the project?"));
    }
    else
    {
        for (int i = 0; i < jarFiles.Num(); ++i)
        {
            classpath += ";";
            classpath += jarFiles[i];
        }
    }

    UE_LOG(LogTemp, Display, TEXT("[JVM] Classpath set with %d dependencies."), jarFiles.Num());

    return classpath;
}

void JavaTestUtil::InitJVM()
{
    if(m_jvm == nullptr)
    {
        FString cpOpt = "-Djava.class.path=" + GetMCPClasspath();
        JavaVMInitArgs vmArgs;
        JavaVMOption vmOptions[4];
        vmOptions[0].optionString = TCHAR_TO_ANSI(*cpOpt);
        vmOptions[1].optionString = "-Xms1m";
        vmOptions[2].optionString = "-Xmx1g";
        vmOptions[3].optionString = "-XX:-OmitStackTraceInFastThrow";
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
            UE_LOG(LogTemp, Fatal, TEXT("Failed to initialize JVM."));
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

void JavaTestUtil::FindAllClasspathJars(FString dir, TArray<FString>& files)
{
    TArray<FString> tmpFiles;
    IFileManager::Get().FindFilesRecursive(
        tmpFiles,
        *dir,
        *FString("*.jar"),
        true,
        false,
        false
    );

    for (int i = 0; i < tmpFiles.Num(); ++i)
    {
        FString file = tmpFiles[i];

        if (file.EndsWith("-sources.jar"))
        {
            UE_LOG(LogTemp, Display, TEXT("[JVM/ClasspathSearch] Filtering out source jar - %s"), *file)
        }
        else
        {
            UE_LOG(LogTemp, Display, TEXT("[JVM/ClasspathSearch] Found jar dependency - %s"), *file);
            files.Add(file);
        }
    }
}
