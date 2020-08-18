#include "CoreMinimal.h"
#include <Util/SharedSeedRandom.h>
#include <Tests/JavaTestUtil.h>

#define NUM_SAMPLES 1000

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSharedSeedRandomTestSetBaseChunkSeed, "MC_UE4.Util.SharedRandomSeed Test SetBaseChunkSeed", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FSharedSeedRandomTestSetBaseChunkSeed::RunTest(const FString& Parameters)
{
    // getting JVM env
    JNIEnv* env = JavaTestUtil::Instance()->GetEnv();

    // Getting reference to java class
    jclass ssrCls = env->FindClass("net/minecraft/util/SharedSeedRandom");
    jmethodID ssrCtor = env->GetMethodID(ssrCls, "<init>", "(J)V");
    jmethodID ssrBaseChunkSeed = env->GetMethodID(ssrCls, "setBaseChunkSeed", "(II)J");

    // Testing numerous sample seeds.
    for(int i = 0; i < NUM_SAMPLES; ++i)
    {
        // Making random filler data
        int seed = rand();
        int x = rand();
        int y = rand();

        // constructing java and c++ versions of class
        jobject jssr = env->NewObject(ssrCls, ssrCtor, (jlong)seed);
        USharedSeedRandom* ssr = NewObject<USharedSeedRandom>();
        ssr->SetSeed((int64_t)seed);

        // getting results from both
        int64_t jresult = env->CallLongMethod(jssr, ssrBaseChunkSeed, (jint)x, (jint)y);
        int64_t result = ssr->SetBaseChunkSeed(x, y);

        // testing results
        FString message = FString::Printf(TEXT("Sample %i, seed=%i, x=%i, y=%i"), i, seed, x, y);
        TestEqual(*message, result, jresult);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSharedSeedRandomTestSetDecorationSeed, "MC_UE4.Util.SharedRandomSeed Test SetDecorationSeed", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FSharedSeedRandomTestSetDecorationSeed::RunTest(const FString& Parameters)
{
    // getting JVM env
    JNIEnv* env = JavaTestUtil::Instance()->GetEnv();

    // Getting reference to java class
    jclass ssrCls = env->FindClass("net/minecraft/util/SharedSeedRandom");
    jmethodID ssrCtor = env->GetMethodID(ssrCls, "<init>", "(J)V");
    jmethodID ssrSetDecorationSeed = env->GetMethodID(ssrCls, "setDecorationSeed", "(JII)J");

    // Testing numerous sample seeds.
    for (int i = 0; i < NUM_SAMPLES; ++i)
    {
        // Making random filler data
        int seed = rand();
        int baseSeed = rand();
        int x = rand();
        int z = rand();

        // constructing java and c++ versions of class
        jobject jssr = env->NewObject(ssrCls, ssrCtor, (jlong)seed);
        USharedSeedRandom* ssr = NewObject<USharedSeedRandom>();
        ssr->SetSeed((int64_t)seed);

        // getting results from both
        int64_t jresult = env->CallLongMethod(jssr, ssrSetDecorationSeed, (jlong)baseSeed, (jint)x, (jint)z);
        int64_t result = ssr->SetDecorationSeed((int64_t)baseSeed, x, z);

        // testing results
        FString message = FString::Printf(TEXT("Sample %i, seed=%i, baseSeed=%i, x=%i, z=%i"), i, seed, baseSeed, x, z);
        TestEqual(*message, result, jresult);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSharedSeedRandomTestSetFeatureSeed, "MC_UE4.Util.SharedRandomSeed Test SetFeatureSeed", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FSharedSeedRandomTestSetFeatureSeed::RunTest(const FString& Parameters)
{
    // getting JVM env
    JNIEnv* env = JavaTestUtil::Instance()->GetEnv();

    // Getting reference to java class
    jclass ssrCls = env->FindClass("net/minecraft/util/SharedSeedRandom");
    jmethodID ssrCtor = env->GetMethodID(ssrCls, "<init>", "(J)V");
    jmethodID ssrSetFeatureSeed = env->GetMethodID(ssrCls, "setFeatureSeed", "(JII)J");

    // Testing numerous sample seeds.
    for (int i = 0; i < NUM_SAMPLES; ++i)
    {
        // Making random filler data
        int seed = rand();
        int baseSeed = rand();
        int x = rand();
        int z = rand();

        // constructing java and c++ versions of class
        jobject jssr = env->NewObject(ssrCls, ssrCtor, (jlong)seed);
        USharedSeedRandom* ssr = NewObject<USharedSeedRandom>();
        ssr->SetSeed((int64_t)seed);

        // getting results from both
        int64_t jresult = env->CallLongMethod(jssr, ssrSetFeatureSeed, (jlong)baseSeed, (jint)x, (jint)z);
        int64_t result = ssr->SetFeatureSeed((int64_t)baseSeed, x, z);

        // testing results
        FString message = FString::Printf(TEXT("Sample %i, seed=%i, baseSeed=%i, x=%i, z=%i"), i, seed, baseSeed, x, z);
        TestEqual(*message, result, jresult);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSharedSeedRandomTestSetLargeFeatureSeed, "MC_UE4.Util.SharedRandomSeed Test SetLargeFeatureSeed", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FSharedSeedRandomTestSetLargeFeatureSeed::RunTest(const FString& Parameters)
{
    // getting JVM env
    JNIEnv* env = JavaTestUtil::Instance()->GetEnv();

    // Getting reference to java class
    jclass ssrCls = env->FindClass("net/minecraft/util/SharedSeedRandom");
    jmethodID ssrCtor = env->GetMethodID(ssrCls, "<init>", "(J)V");
    jmethodID ssrSetLargeFeatureSeed = env->GetMethodID(ssrCls, "setLargeFeatureSeed", "(JII)J");

    // Testing numerous sample seeds.
    for (int i = 0; i < NUM_SAMPLES; ++i)
    {
        // Making random filler data
        int seed = rand();
        int baseSeed = rand();
        int x = rand();
        int z = rand();

        // constructing java and c++ versions of class
        jobject jssr = env->NewObject(ssrCls, ssrCtor, (jlong)seed);
        USharedSeedRandom* ssr = NewObject<USharedSeedRandom>();
        ssr->SetSeed((int64_t)seed);

        // getting results from both
        int64_t jresult = env->CallLongMethod(jssr, ssrSetLargeFeatureSeed, (jlong)baseSeed, (jint)x, (jint)z);
        int64_t result = ssr->SetLargeFeatureSeed((int64_t)baseSeed, x, z);

        // testing results
        FString message = FString::Printf(TEXT("Sample %i, seed=%i, baseSeed=%i, x=%i, z=%i"), i, seed, baseSeed, x, z);
        TestEqual(*message, result, jresult);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSharedSeedRandomTestSetLargeFeatureSeedWithSalt, "MC_UE4.Util.SharedRandomSeed Test SetLargeFeatureSeedWithSalt", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FSharedSeedRandomTestSetLargeFeatureSeedWithSalt::RunTest(const FString& Parameters)
{
    // getting JVM env
    JNIEnv* env = JavaTestUtil::Instance()->GetEnv();

    // Getting reference to java class
    jclass ssrCls = env->FindClass("net/minecraft/util/SharedSeedRandom");
    jmethodID ssrCtor = env->GetMethodID(ssrCls, "<init>", "(J)V");
    jmethodID ssrSetLargeFeatureSeedWithSalt = env->GetMethodID(ssrCls, "setLargeFeatureSeedWithSalt", "(JIII)J");

    // Testing numerous sample seeds.
    for (int i = 0; i < NUM_SAMPLES; ++i)
    {
        // Making random filler data
        int seed = rand();
        int baseSeed = rand();
        int x = rand();
        int z = rand();
        int modifier = rand();

        // constructing java and c++ versions of class
        jobject jssr = env->NewObject(ssrCls, ssrCtor, (jlong)seed);
        USharedSeedRandom* ssr = NewObject<USharedSeedRandom>();
        ssr->SetSeed((int64_t)seed);

        // getting results from both
        int64_t jresult = env->CallLongMethod(jssr, ssrSetLargeFeatureSeedWithSalt, (jlong)baseSeed, (jint)x, (jint)z, (jint)modifier);
        int64_t result = ssr->SetLargeFeatureSeedWithSalt((int64_t)baseSeed, x, z, modifier);

        // testing results
        FString message = FString::Printf(TEXT("Sample %i, seed=%i, baseSeed=%i, x=%i, z=%i, modifier=%i"), i, seed, baseSeed, x, z, modifier);
        TestEqual(*message, result, jresult);
    }

    return true;
}