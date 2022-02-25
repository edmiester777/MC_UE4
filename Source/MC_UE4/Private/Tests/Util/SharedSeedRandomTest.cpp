#include <Util/SharedSeedRandom.h>
#include "CoreMinimal.h"
#include <TestUtil/JavaTestUtil.h>
#include "SharedSeedRandomTest.h"

#define NUM_SAMPLES 1000

void InitSharedSeedRandomJVM(long seed, jclass& ssrCls, jobject& ssr)
{
    ssrCls = JNI_ENV->FindClass("net/minecraft/util/SharedSeedRandom");
    jmethodID ssrCtor = JNI_ENV->GetMethodID(ssrCls, "<init>", "(J)V");
    ssr = JNI_ENV->NewObject(ssrCls, ssrCtor, (jlong)seed);
}

USharedSeedRandom* InitSharedSeedRandom(long seed)
{
    USharedSeedRandom* ssr = NewObject<USharedSeedRandom>();
    ssr->SetSeed(seed);
    return ssr;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSharedSeedRandomTestSetBaseChunkSeed, "MC_UE4.Util.SharedRandomSeed Test SetBaseChunkSeed", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FSharedSeedRandomTestSetBaseChunkSeed::RunTest(const FString& Parameters)
{
    JNI_CLEAR_ERROR;

    // Testing numerous sample seeds.
    for(int i = 0; i < NUM_SAMPLES; ++i)
    {
        // Making random filler data
        int seed = rand();
        int x = rand();
        int y = rand();

        // constructing java and c++ versions of class
        jclass ssrCls;
        jobject jssr;
        InitSharedSeedRandomJVM(seed, ssrCls, jssr);
        USharedSeedRandom* ssr = InitSharedSeedRandom(seed);
        JNI_TEST_CHECK_AND_PRINT_ERROR;

        // getting results from both
        jmethodID ssrBaseChunkSeed = JNI_ENV->GetMethodID(ssrCls, "setBaseChunkSeed", "(II)J");
        int64_t jresult = JNI_ENV->CallLongMethod(jssr, ssrBaseChunkSeed, (jint)x, (jint)y);
        int64_t result = ssr->SetBaseChunkSeed(x, y);
        JNI_TEST_CHECK_AND_PRINT_ERROR;

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
    JNI_CLEAR_ERROR;

    // Testing numerous sample seeds.
    for (int i = 0; i < NUM_SAMPLES; ++i)
    {
        // Making random filler data
        int seed = rand();
        int baseSeed = rand();
        int x = rand();
        int z = rand();

        // constructing java and c++ versions of class
        jclass ssrCls;
        jobject jssr;
        InitSharedSeedRandomJVM(seed, ssrCls, jssr);
        USharedSeedRandom* ssr = InitSharedSeedRandom(seed);
        JNI_TEST_CHECK_AND_PRINT_ERROR;

        // getting results from both
        jmethodID ssrSetDecorationSeed = JNI_ENV->GetMethodID(ssrCls, "setDecorationSeed", "(JII)J");
        int64_t jresult = JNI_ENV->CallLongMethod(jssr, ssrSetDecorationSeed, (jlong)baseSeed, (jint)x, (jint)z);
        int64_t result = ssr->SetDecorationSeed((int64_t)baseSeed, x, z);
        JNI_TEST_CHECK_AND_PRINT_ERROR;

        // testing results
        FString message = FString::Printf(TEXT("Sample %i, seed=%i, baseSeed=%i, x=%i, z=%i"), i, seed, baseSeed, x, z);
        TestEqual(*message, result, jresult);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSharedSeedRandomTestSetFeatureSeed, "MC_UE4.Util.SharedRandomSeed Test SetFeatureSeed", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FSharedSeedRandomTestSetFeatureSeed::RunTest(const FString& Parameters)
{
    JNI_CLEAR_ERROR;

    // Testing numerous sample seeds.
    for (int i = 0; i < NUM_SAMPLES; ++i)
    {
        // Making random filler data
        int seed = rand();
        int baseSeed = rand();
        int x = rand();
        int z = rand();

        // constructing java and c++ versions of class
        jclass ssrCls;
        jobject jssr;
        InitSharedSeedRandomJVM(seed, ssrCls, jssr);
        USharedSeedRandom* ssr = InitSharedSeedRandom(seed);
        JNI_TEST_CHECK_AND_PRINT_ERROR;

        // getting results from both
        jmethodID ssrSetFeatureSeed = JNI_ENV->GetMethodID(ssrCls, "setFeatureSeed", "(JII)J");
        int64_t jresult = JNI_ENV->CallLongMethod(jssr, ssrSetFeatureSeed, (jlong)baseSeed, (jint)x, (jint)z);
        int64_t result = ssr->SetFeatureSeed((int64_t)baseSeed, x, z);
        JNI_TEST_CHECK_AND_PRINT_ERROR;

        // testing results
        FString message = FString::Printf(TEXT("Sample %i, seed=%i, baseSeed=%i, x=%i, z=%i"), i, seed, baseSeed, x, z);
        TestEqual(*message, result, jresult);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSharedSeedRandomTestSetLargeFeatureSeed, "MC_UE4.Util.SharedRandomSeed Test SetLargeFeatureSeed", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FSharedSeedRandomTestSetLargeFeatureSeed::RunTest(const FString& Parameters)
{
    JNI_CLEAR_ERROR;

    // Testing numerous sample seeds.
    for (int i = 0; i < NUM_SAMPLES; ++i)
    {
        // Making random filler data
        int seed = rand();
        int baseSeed = rand();
        int x = rand();
        int z = rand();

        // constructing java and c++ versions of class
        jclass ssrCls;
        jobject jssr;
        InitSharedSeedRandomJVM(seed, ssrCls, jssr);
        USharedSeedRandom* ssr = InitSharedSeedRandom(seed);
        JNI_TEST_CHECK_AND_PRINT_ERROR;

        // getting results from both
        jmethodID ssrSetLargeFeatureSeed = JNI_ENV->GetMethodID(ssrCls, "setLargeFeatureSeed", "(JII)J");
        int64_t jresult = JNI_ENV->CallLongMethod(jssr, ssrSetLargeFeatureSeed, (jlong)baseSeed, (jint)x, (jint)z);
        int64_t result = ssr->SetLargeFeatureSeed((int64_t)baseSeed, x, z);
        JNI_TEST_CHECK_AND_PRINT_ERROR;

        // testing results
        FString message = FString::Printf(TEXT("Sample %i, seed=%i, baseSeed=%i, x=%i, z=%i"), i, seed, baseSeed, x, z);
        TestEqual(*message, result, jresult);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSharedSeedRandomTestSetLargeFeatureSeedWithSalt, "MC_UE4.Util.SharedRandomSeed Test SetLargeFeatureSeedWithSalt", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FSharedSeedRandomTestSetLargeFeatureSeedWithSalt::RunTest(const FString& Parameters)
{
    JNI_CLEAR_ERROR;

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
        jclass ssrCls;
        jobject jssr;
        InitSharedSeedRandomJVM(seed, ssrCls, jssr);
        USharedSeedRandom* ssr = InitSharedSeedRandom(seed);
        JNI_TEST_CHECK_AND_PRINT_ERROR;

        // getting results from both
        jmethodID ssrSetLargeFeatureSeedWithSalt = JNI_ENV->GetMethodID(ssrCls, "setLargeFeatureSeedWithSalt", "(JIII)J");
        int64_t jresult = JNI_ENV->CallLongMethod(jssr, ssrSetLargeFeatureSeedWithSalt, (jlong)baseSeed, (jint)x, (jint)z, (jint)modifier);
        int64_t result = ssr->SetLargeFeatureSeedWithSalt((int64_t)baseSeed, x, z, modifier);
        JNI_TEST_CHECK_AND_PRINT_ERROR;

        // testing results
        FString message = FString::Printf(TEXT("Sample %i, seed=%i, baseSeed=%i, x=%i, z=%i, modifier=%i"), i, seed, baseSeed, x, z, modifier);
        TestEqual(*message, result, jresult);
    }

    return true;
}