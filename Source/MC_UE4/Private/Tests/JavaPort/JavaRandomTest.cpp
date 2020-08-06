// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreMinimal.h"
#include <JavaPort/JavaRandom.h>
#include <bitset>
#include <Tests/JavaTestUtil.h>

#define NUM_SAMPLES 1000

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJavaRandomNextTest, "MC_UE4.JavaPort.Random Next Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FJavaRandomNextTest::RunTest(const FString& Parameters)
{
    // Getting java definitions
    JNIEnv* env = JavaTestUtil::instance()->GetEnv();
    jclass randomCls = env->FindClass("java/util/Random");
    jmethodID randomCtor = env->GetMethodID(randomCls, "<init>", "(J)V");
    jmethodID nextMethod = env->GetMethodID(randomCls, "next", "(I)I");

    // comparing results from various seeds
    for(int i = 0; i < NUM_SAMPLES; ++i) {
        // getting random seed value
        int seed = rand();

        // constructing java and unreal versions of random class
        jobject jrandom = env->NewObject(randomCls, randomCtor, (jlong)seed);
        UJavaRandom* random = NewObject<UJavaRandom>();
        random->SetSeed((int64_t)seed);

        // testing results under subsequent calls
        for(int j = 0; j < 10; ++j)
        {
            // getting result of java random
            int32_t jresult = (int32_t)env->CallIntMethod(jrandom, nextMethod, 27);

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
    // getting Java definitions
    JNIEnv* env = JavaTestUtil::instance()->GetEnv();
    jclass randomCls = env->FindClass("java/util/Random");
    jmethodID randomCtor = env->GetMethodID(randomCls, "<init>", "(J)V");
    jmethodID nextIntMethod = env->GetMethodID(randomCls, "nextInt", "()I");

    // comparing results from various seeds
    for (int i = 0; i < NUM_SAMPLES; ++i)
    {
        // getting random seed
        int seed = rand();

        // constructing java and unreal versions of random class
        jobject jrandom = env->NewObject(randomCls, randomCtor, (jlong)seed);
        UJavaRandom* random = NewObject<UJavaRandom>();
        random->SetSeed(seed);

        // testing results under subsequent calls
        for(int j = 0; j < 10; ++j)
        {
            // getting result of java random
            int32_t jresult = (int32_t)env->CallIntMethod(jrandom, nextIntMethod);

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
    // getting Java definitions
    JNIEnv* env = JavaTestUtil::instance()->GetEnv();
    jclass randomCls = env->FindClass("java/util/Random");
    jmethodID randomCtor = env->GetMethodID(randomCls, "<init>", "(J)V");
    jmethodID nextIntMethod = env->GetMethodID(randomCls, "nextInt", "(I)I");

    // comparing results from various seeds
    for (int i = 0; i < NUM_SAMPLES; ++i)
    {
        // getting random seed
        int seed = rand();

        // constructing java and unreal versions of random class
        jobject jrandom = env->NewObject(randomCls, randomCtor, (jlong)seed);
        UJavaRandom* random = NewObject<UJavaRandom>();
        random->SetSeed(seed);

        // testing results under subsequent calls
        for (int j = 0; j < 10; ++j)
        {
            // generating bound to pass to this function
            int bound = rand() % 255;

            // getting result of java random
            int32_t jresult = (int32_t)env->CallIntMethod(jrandom, nextIntMethod, (jint)bound);

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
    // getting Java definitions
    JNIEnv* env = JavaTestUtil::instance()->GetEnv();
    jclass randomCls = env->FindClass("java/util/Random");
    jmethodID randomCtor = env->GetMethodID(randomCls, "<init>", "(J)V");
    jmethodID nextDoubleMethod = env->GetMethodID(randomCls, "nextDouble", "()D");

    // comparing results from various seeds
    for (int i = 0; i < NUM_SAMPLES; ++i)
    {
        // getting random seed
        int seed = rand();

        // constructing java and unreal versions of random class
        jobject jrandom = env->NewObject(randomCls, randomCtor, (jlong)seed);
        UJavaRandom* random = NewObject<UJavaRandom>();
        random->SetSeed(seed);

        // testing results under subsequent calls
        for (int j = 0; j < 10; ++j)
        {
            // getting result of java random
            double jresult = (double)env->CallDoubleMethod(jrandom, nextDoubleMethod);

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
    // getting Java definitions
    JNIEnv* env = JavaTestUtil::instance()->GetEnv();
    jclass randomCls = env->FindClass("java/util/Random");
    jmethodID randomCtor = env->GetMethodID(randomCls, "<init>", "(J)V");
    jmethodID nextLongMethod = env->GetMethodID(randomCls, "nextLong", "()J");

    // comparing results from various seeds
    for (int i = 0; i < NUM_SAMPLES; ++i)
    {
        // getting random seed
        int seed = rand();

        // constructing java and unreal versions of random class
        jobject jrandom = env->NewObject(randomCls, randomCtor, (jlong)seed);
        UJavaRandom* random = NewObject<UJavaRandom>();
        random->SetSeed(seed);

        // testing results under subsequent calls
        for (int j = 0; j < 10; ++j)
        {
            // getting result of java random
            int64_t jresult = (int64_t)env->CallLongMethod(jrandom, nextLongMethod);

            // getting result of our implementation
            int64_t result = random->NextLong();

            // comparing results
            FString message = FString::Printf(TEXT("Result iteration %d.%d - Seed %l"), i, j, seed);
            TestEqual(message, result, jresult);
        }
    }

    return true;
}