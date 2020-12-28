// Fill out your copyright notice in the Description page of Project Settings.


#include "JavaRandomTest.h"
#include <Tests/JavaTestUtil.h>

#define NUM_SAMPLES 1000

void InitJavaRandomJVM(long seed, jclass& jrandomCls, jobject& jrandom)
{
    // finding class
    jrandomCls = JNI_ENV->FindClass("java/util/Random");

    // geting constructor on class
    jmethodID jrandomCtor = JNI_ENV->GetMethodID(jrandomCls, "<init>", "(J)V");

    // constructing object
    jrandom = JNI_ENV->NewObject(jrandomCls, jrandomCtor, (jlong)seed);
}

UJavaRandom* InitJavaRandom(long seed)
{
    UJavaRandom* random = NewObject<UJavaRandom>();
    random->SetSeed(seed);
    return random;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJavaRandomNextTest, "MC_UE4.JavaPort.Random Next Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FJavaRandomNextTest::RunTest(const FString& Parameters)
{
    JNI_CLEAR_ERROR;

    // comparing results from various seeds
    for(int i = 0; i < NUM_SAMPLES; ++i) {
        // getting random seed value
        int seed = rand();

        // initializing jvm random class
        jclass jrandomCls;
        jobject jrandom;
        InitJavaRandomJVM(seed, jrandomCls, jrandom);
        JNI_TEST_CHECK_AND_PRINT_ERROR;

        // getting the next method
        jmethodID nextMethod = JNI_ENV->GetMethodID(jrandomCls, "next", "(I)I");

        // constructing java and unreal versions of random class
        UJavaRandom* random = InitJavaRandom(seed);

        // testing results under subsequent calls
        for(int j = 0; j < 10; ++j)
        {
            // getting result of java random
            int32_t jresult = (int32_t)JNI_ENV->CallIntMethod(jrandom, nextMethod, 27);
            JNI_TEST_CHECK_AND_PRINT_ERROR;

            // getting result of our implementation
            int32_t result = random->Next(27);

            // comparing results
            FString message = FString::Printf(TEXT("Result iteration %i.%i - Seed %l"), i, j, seed);
            TestEqual(message, result, jresult);
        }
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJavaRandomTestNextInt, "MC_UE4.JavaPort.Random Test Next Int", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FJavaRandomTestNextInt::RunTest(const FString& Parameters)
{
    JNI_CLEAR_ERROR;

    // comparing results from various seeds
    for (int i = 0; i < NUM_SAMPLES; ++i)
    {
        // getting random seed
        int seed = rand();

        // constructing java and unreal versions of random class
        jclass jrandomCls;
        jobject jrandom;
        InitJavaRandomJVM(seed, jrandomCls, jrandom);
        UJavaRandom* random = InitJavaRandom(seed);
        JNI_TEST_CHECK_AND_PRINT_ERROR;

        // getting the nextInt method from the JVM
        jmethodID nextIntMethod = JNI_ENV->GetMethodID(jrandomCls, "nextInt", "()I");

        // testing results under subsequent calls
        for(int j = 0; j < 10; ++j)
        {
            // getting result of java random
            int32_t jresult = (int32_t)JNI_ENV->CallIntMethod(jrandom, nextIntMethod);
            JNI_TEST_CHECK_AND_PRINT_ERROR;

            // getting result of our implementation
            int32_t result = random->NextInt();

            // comparing results
            FString message = FString::Printf(TEXT("Result iteration %i.%i - Seed %l"), i, j, seed);
            TestEqual(message, result, jresult);
        }
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJavaRandomTestNextIntBounds, "MC_UE4.JavaPort.Random Test Next Int With Bounds", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FJavaRandomTestNextIntBounds::RunTest(const FString& Parameters)
{
    JNI_CLEAR_ERROR;

    // comparing results from various seeds
    for (int i = 0; i < NUM_SAMPLES; ++i)
    {
        // getting random seed
        int seed = rand();

        // constructing java and unreal versions of random class
        jclass jrandomCls;
        jobject jrandom;
        InitJavaRandomJVM(seed, jrandomCls, jrandom);
        UJavaRandom* random = InitJavaRandom(seed);
        JNI_TEST_CHECK_AND_PRINT_ERROR;

        // getting the nextInt method from JVM
        jmethodID nextIntMethod = JNI_ENV->GetMethodID(jrandomCls, "nextInt", "(I)I");

        // testing results under subsequent calls
        for (int j = 0; j < 10; ++j)
        {
            // generating bound to pass to this function
            int bound = abs(rand() % 255) + 1;

            // getting result of java random
            int32_t jresult = (int32_t)JNI_ENV->CallIntMethod(jrandom, nextIntMethod, (jint)bound);
            JNI_TEST_CHECK_AND_PRINT_ERROR;

            // getting result of our implementation
            int32_t result = random->NextInt(bound);

            // comparing results
            FString message = FString::Printf(TEXT("Result iteration %i.%i - Seed %l"), i, j, seed);
            TestEqual(message, result, jresult);
        }
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJavaRandomTestNextDouble, "MC_UE4.JavaPort.Random Test Next Double", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FJavaRandomTestNextDouble::RunTest(const FString& Parameters)
{
    JNI_CLEAR_ERROR;

    // comparing results from various seeds
    for (int i = 0; i < NUM_SAMPLES; ++i)
    {
        // getting random seed
        int seed = rand();

        // constructing java and unreal versions of random class
        jclass jrandomCls;
        jobject jrandom;
        InitJavaRandomJVM(seed, jrandomCls, jrandom);
        jmethodID nextDoubleMethod = JNI_ENV->GetMethodID(jrandomCls, "nextDouble", "()D");
        UJavaRandom* random = InitJavaRandom(seed);
        JNI_TEST_CHECK_AND_PRINT_ERROR;

        // testing results under subsequent calls
        for (int j = 0; j < 10; ++j)
        {
            // getting result of java random
            double jresult = (double)JNI_ENV->CallDoubleMethod(jrandom, nextDoubleMethod);
            JNI_TEST_CHECK_AND_PRINT_ERROR;

            // getting result of our implementation
            double result = random->NextDouble();

            // comparing results
            FString message = FString::Printf(TEXT("Result iteration %d.%d - Seed %l"), i, j, seed);
            TestEqual(message, result, jresult);
        }
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJavaRandomTestNextLongPositive1Seed, "MC_UE4.JavaPort.Random Test Next Long From Positive 1 Seed", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FJavaRandomTestNextLongPositive1Seed::RunTest(const FString& Parameters)
{
    JNI_CLEAR_ERROR;

    // comparing results from various seeds
    for (int i = 0; i < NUM_SAMPLES; ++i)
    {
        // getting random seed
        int seed = rand();

        // constructing java and unreal versions of random class
        jclass jrandomCls;
        jobject jrandom;
        InitJavaRandomJVM(seed, jrandomCls, jrandom);
        jmethodID nextLongMethod = JNI_ENV->GetMethodID(jrandomCls, "nextLong", "()J");
        UJavaRandom* random = InitJavaRandom(seed);
        JNI_TEST_CHECK_AND_PRINT_ERROR;

        // testing results under subsequent calls
        for (int j = 0; j < 10; ++j)
        {
            // getting result of java random
            int64_t jresult = (int64_t)JNI_ENV->CallLongMethod(jrandom, nextLongMethod);
            JNI_TEST_CHECK_AND_PRINT_ERROR;

            // getting result of our implementation
            int64_t result = random->NextLong();

            // comparing results
            FString message = FString::Printf(TEXT("Result iteration %d.%d - Seed %l"), i, j, seed);
            TestEqual(message, result, jresult);
        }
    }

    return true;
}