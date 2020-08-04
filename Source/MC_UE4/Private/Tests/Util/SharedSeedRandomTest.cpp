#include "CoreMinimal.h"
#include <Util/SharedSeedRandom.h>

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSharedRandomSeedTestSetBaseChunkSeed, "MC_UE4.Util.SharedRandomSeed Test SetBaseChunkSeed From Positive 1 Seed", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FSharedRandomSeedTestSetBaseChunkSeed::RunTest(const FString& Parameters)
{
    const int NUM_RESULTS = 5;
    int64_t expectedResults[] = {
        0,
        474771116253,
        949542232506,
        1424313348759,
        1899084465012
    };

    USharedSeedRandom* random = NewObject<USharedSeedRandom>();
    random->SetSeed(1);

    for(int i = 0; i < NUM_RESULTS; ++i) 
    {
        int64_t result = random->SetBaseChunkSeed(i, i);
        TestEqual("Result " + FString::FromInt(i + 1), result, expectedResults[i]);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSharedRandomSeedTestSetDecorationSeed, "MC_UE4.Util.SharedRandomSeed Test SetDecorationSeed From Positive 1 Seed", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FSharedRandomSeedTestSetDecorationSeed::RunTest(const FString& Parameters)
{
    const int NUM_RESULTS = 5;
    int64_t expectedResults[] = {
        1,
        2600234921859913325,
        5200469843719826649,
        7800704765579739973,
        -8045804386269898319
    };

    USharedSeedRandom* random = NewObject<USharedSeedRandom>();
    random->SetSeed(1);

    for (int i = 0; i < NUM_RESULTS; ++i)
    {
        int64_t result = random->SetDecorationSeed(1L, i, i);
        TestEqual("Result " + FString::FromInt(i + 1), result, expectedResults[i]);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSharedRandomSeedTestSetFeatureSeed, "MC_UE4.Util.SharedRandomSeed Test SetFeatureSeed From Positive 1 Seed", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FSharedRandomSeedTestSetFeatureSeed::RunTest(const FString& Parameters)
{
    const int NUM_RESULTS = 5;
    int64_t expectedResults[] = {
        1,
        10002, 
        20003,
        30004,
        40005
    };

    USharedSeedRandom* random = NewObject<USharedSeedRandom>();
    random->SetSeed(1);

    for (int i = 0; i < NUM_RESULTS; ++i)
    {
        int64_t result = random->SetFeatureSeed(1L, i, i);
        TestEqual("Result " + FString::FromInt(i + 1), result, expectedResults[i]);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSharedRandomSeedTestSetLargeFeatureSeed, "MC_UE4.Util.SharedRandomSeed Test SetLargeFeatureSeed From Positive 1 Seed", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FSharedRandomSeedTestSetLargeFeatureSeed::RunTest(const FString& Parameters)
{
    const int NUM_RESULTS = 5;
    int64_t expectedResults[] = {
        1,
        -3179018946729384629,
        -6358037893458769259,
        838139122915752511,
        5730668286792013097
    };

    USharedSeedRandom* random = NewObject<USharedSeedRandom>();
    random->SetSeed(1);

    for (int i = 0; i < NUM_RESULTS; ++i)
    {
        int64_t result = random->SetLargeFeatureSeed(1L, i, i);
        TestEqual("Result " + FString::FromInt(i + 1), result, expectedResults[i]);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSharedRandomSeedTestSetLargeFeatureSeedWithSalt, "MC_UE4.Util.SharedRandomSeed Test SetLargeFeatureSeedWithSalt From Positive 1 Seed", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FSharedRandomSeedTestSetLargeFeatureSeedWithSalt::RunTest(const FString& Parameters)
{
    const int NUM_RESULTS = 5;
    int64_t expectedResults[] = {
        11,
        474771116264,
        949542232517,
        1424313348770,
        1899084465023
    };

    USharedSeedRandom* random = NewObject<USharedSeedRandom>();
    random->SetSeed(1);

    for (int i = 0; i < NUM_RESULTS; ++i)
    {
        int64_t result = random->SetLargeFeatureSeedWithSalt(1L, i, i, 10);
        TestEqual("Result " + FString::FromInt(i + 1), result, expectedResults[i]);
    }

    return true;
}