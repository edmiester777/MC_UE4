#include "CoreMinimal.h"
#include <Util/SharedSeedRandom.h>
#include <World/Gen/PerlinNoiseGenerator.h>

TArray<int> PerlinNoiseTest_GetIntArr()
{
    TArray<int> arr;
    arr.Add(12);
    arr.Add(15);
    arr.Add(19);
    arr.Add(49);
    arr.Add(890);
    arr.Add(900);
    return arr;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPerlinNoiseGeneratorTestInit, "MC_UE4.World.Gen.PerlinNoiseGenerator Test Initialization of Perlin Noise Generator.", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FPerlinNoiseGeneratorTestInit::RunTest(const FString& Parameters)
{
    const double expectedXO = 2.4228908772695546E-268;
    const double expectedYO = 8.452712498170644E270;

    TArray<int> expectedNonZeroNoiseLevels;
    expectedNonZeroNoiseLevels.Add(0);
    expectedNonZeroNoiseLevels.Add(10);
    expectedNonZeroNoiseLevels.Add(851);
    expectedNonZeroNoiseLevels.Add(881);
    expectedNonZeroNoiseLevels.Add(885);
    expectedNonZeroNoiseLevels.Add(888);

    USharedSeedRandom* seed = NewObject<USharedSeedRandom>();
    seed->SetSeed(1);
    UPerlinNoiseGenerator* gen = NewObject<UPerlinNoiseGenerator>();
    gen->Init(*seed, PerlinNoiseTest_GetIntArr());

    TestEqual("XO Value", gen->m_xo, expectedXO);
    TestEqual("YO Value", gen->m_yo, expectedYO);

    // checking that noise levels were generated correctly.
    for(int i = 0; i < gen->m_noiseLevels.Num(); ++i)
    {
        USimplexNoiseGenerator* nptr = gen->m_noiseLevels[i];
        if (expectedNonZeroNoiseLevels.Contains(i))
            TestNotEqual(TEXT("Expected Non-Zero pointer value at index ") + FString::FromInt(i), (void *)nptr, (void *)nullptr);
        else
            TestEqual(TEXT("Expected zero pointer value at index ") + FString::FromInt(i), (void *)nptr, (void *)nullptr);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPerlinNoiseGeneratorTestNoiseAtXY, "MC_UE4.World.Gen.PerlinNoiseGenerator Test NoiseAt with XY function.", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FPerlinNoiseGeneratorTestNoiseAtXY::RunTest(const FString& Parameters)
{
    const int NUM_RESULTS = 5;
    const double expectedResults[NUM_RESULTS] = {
        0.2073906103127365,
        0.11315628294392532,
        0.23598397136313534,
        -0.17770651932035997,
        0.2359227138577469
    };

    USharedSeedRandom* seed = NewObject<USharedSeedRandom>();
    seed->SetSeed(1);
    UPerlinNoiseGenerator* gen = NewObject<UPerlinNoiseGenerator>();
    gen->Init(*seed, PerlinNoiseTest_GetIntArr());

    for(int i = 0; i < NUM_RESULTS; ++i)
    {
        double result = gen->NoiseAt(i, i * 10, true);
        TestEqual("Result of NoiseAt", result, expectedResults[i]);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPerlinNoiseGeneratorTestNoiseAtXYZ, "MC_UE4.World.Gen.PerlinNoiseGenerator Test NoiseAt with XYZ function.", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FPerlinNoiseGeneratorTestNoiseAtXYZ::RunTest(const FString& Parameters)
{
    const int NUM_RESULTS = 5;
    const double expectedResults[NUM_RESULTS] = {
        0.1140648356720051,
        0.062235955619158935,
        0.12979118424972444,
        -0.09773858562619799,
        0.1297574926217608
    };

    USharedSeedRandom* seed = NewObject<USharedSeedRandom>();
    seed->SetSeed(1);
    UPerlinNoiseGenerator* gen = NewObject<UPerlinNoiseGenerator>();
    gen->Init(*seed, PerlinNoiseTest_GetIntArr());

    for (int i = 0; i < NUM_RESULTS; ++i)
    {
        double result = gen->NoiseAt(i, i * 10, i, i * 10);
        TestEqual("Result of NoiseAt", result, expectedResults[i]);
    }

    return true;
}