// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreMinimal.h"
#include <JavaPort/JavaRandom.h>

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJavaRandomNextTestPositive1Seed, "MC_UE4.JavaPort.Random Next Test From Positive 1 Seed", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FJavaRandomNextTestPositive1Seed::RunTest(const FString& Parameters)
{
    const int NUM_RESULTS = 5;
    const int NUM_BITS = 27;
    int64_t expectedSeeds[] = {
        25214903916,
        205723924636679,
        28280696119558,
        115427488297881,
        114684108877360
    };
    int64_t expectedResults[] = {
        98096811,
        13485286,
        55040115,
        54685644,
        27879015
    };

    UJavaRandom* random = NewObject<UJavaRandom>();
    random->SetSeed(1);

    for(int i = 0; i < NUM_RESULTS; ++i)
    {
        TestEqual("Seed " + FString::FromInt(i + 1), (long long)random->m_seed, (long long)expectedSeeds[i]);
        int64_t result = random->Next(NUM_BITS);
        TestEqual(TEXT("Result ") + FString::FromInt(i + 1), (long long)result, (long long)expectedResults[i]);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJavaRandomNextTestNegative1Seed, "MC_UE4.JavaPort.Random Next Test From Negative 1 Seed", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FJavaRandomNextTestNegative1Seed::RunTest(const FString& Parameters)
{
    const int NUM_RESULTS = 5;
    const int NUM_BITS = 27;
    int64_t expectedSeeds[] = {
        281449761806738,
        75700622266165,
        123725706106780,
        3453692097911,
        154258039025078
    };
    int64_t expectedResults[] = {
        36096869,
        58997014,
        1646848,
        73555964,
        88863475
    };

    UJavaRandom* random = NewObject<UJavaRandom>();
    random->SetSeed(-1);

    for (int i = 0; i < NUM_RESULTS; ++i)
    {
        TestEqual("Seed " + FString::FromInt(i + 1), (long long)random->m_seed, (long long)expectedSeeds[i]);
        int64_t result = random->Next(NUM_BITS);
        TestEqual(TEXT("Result ") + FString::FromInt(i + 1), (long long)result, (long long)expectedResults[i]);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJavaRandomTestNextIntPositive1Seed, "MC_UE4.JavaPort.Random Test Next Int From Positive 1 Seed", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FJavaRandomTestNextIntPositive1Seed::RunTest(const FString& Parameters)
{
    // expected result from NextDouble if seed is 1
    const int NUM_RESULTS = 5;
    int32_t expectedResults[] = {
        -1155869325,
        431529176,
        1761283695,
        1749940626,
        892128508
    };

    UJavaRandom* random = NewObject<UJavaRandom>();
    random->SetSeed(1);

    for (int i = 0; i < NUM_RESULTS; ++i)
    {
        int32_t result = random->NextInt();
        TestEqual(TEXT("Result ") + FString::FromInt(i + 1), result, expectedResults[i]);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJavaRandomTestNextIntBoundsPositive1Seed, "MC_UE4.JavaPort.Random Test Next Int With Bounds From Positive 1 Seed", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FJavaRandomTestNextIntBoundsPositive1Seed::RunTest(const FString& Parameters)
{
    // expected result from NextDouble if seed is 1
    const int NUM_RESULTS = 4;
    int32_t expectedResults[] = {
        0,
        5,
        163,
        10598022
    };

    UJavaRandom* random = NewObject<UJavaRandom>();
    random->SetSeed(1);

    int32_t results[] = {
        random->NextInt(0),
        random->NextInt(10),
        random->NextInt(0xFF),
        random->NextInt(24858395)
    };

    for (int i = 0; i < NUM_RESULTS; ++i)
    {
        TestEqual(TEXT("Result ") + FString::FromInt(i + 1), results[i], expectedResults[i]);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJavaRandomTestNextDoublePositive1Seed, "MC_UE4.JavaPort.RandomTest Next Double From Positive 1 Seed", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FJavaRandomTestNextDoublePositive1Seed::RunTest(const FString& Parameters)
{
    // expected result from NextDouble if seed is 1
    const int NUM_RESULTS = 5;
    double expectedResults[] = {
        0.7308781907032909,
        0.41008081149220166,
        0.20771484130971707,
        0.3327170559595112,
        0.9677559094241207
    };

    UJavaRandom* random = NewObject<UJavaRandom>();
    random->SetSeed(1);

    for(int i = 0; i < NUM_RESULTS; ++i)
    {
        double result = random->NextDouble();
        TestEqual(TEXT("Result ") + FString::FromInt(i + 1), result, expectedResults[i]);
    }

    return true;
}
