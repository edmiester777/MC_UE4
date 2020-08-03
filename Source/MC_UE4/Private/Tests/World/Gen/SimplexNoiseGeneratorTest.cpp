#include "CoreMinimal.h"
#include <World/Gen/SimplexNoiseGenerator.h>

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSimplexNoiseGeneratorTestInit, "MC_UE4.World.Gen.SimplexNoiseGenerator Test Initialization of Simplex Noise Generator.", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FSimplexNoiseGeneratorTestInit::RunTest(const FString& Parameters)
{
    const int NUM_RANDOMS = 512;
    double expectedXO = 187.10481682004246;
    double expectedYO = 104.98068774200362;
    double expectedZO = 53.17499937528757;
    int32_t expectedRandoms[512] = { 85, 92, 42, 62, 65, 212, 73, 40, 50, 246, 162, 18, 80, 234, 20, 200, 206, 187, 148, 177, 82, 74, 151, 84, 141, 12, 166, 122, 171, 72, 191, 226, 59, 96, 221, 149, 93, 97, 79, 63, 52, 139, 21, 216, 240, 251, 252, 194, 15, 104, 49, 255, 156, 225, 160, 86, 142, 153, 218, 83, 23, 215, 195, 161, 227, 56, 111, 39, 238, 24, 68, 207, 185, 123, 13, 51, 237, 172, 137, 180, 235, 45, 64, 102, 253, 118, 170, 31, 69, 189, 249, 152, 144, 204, 208, 233, 190, 61, 33, 3, 196, 179, 95, 230, 71, 130, 8, 250, 76, 103, 143, 131, 58, 242, 55, 138, 146, 213, 124, 29, 181, 37, 136, 243, 44, 94, 7, 81, 199, 186, 168, 77, 38, 140, 220, 88, 247, 1, 201, 35, 17, 116, 114, 164, 154, 158, 128, 70, 241, 66, 60, 132, 14, 163, 53, 165, 117, 182, 223, 198, 133, 5, 112, 174, 115, 203, 248, 176, 0, 183, 2, 99, 75, 67, 4, 126, 30, 87, 109, 210, 22, 98, 192, 155, 127, 48, 36, 175, 78, 119, 32, 231, 100, 121, 232, 157, 135, 244, 47, 224, 228, 150, 105, 167, 57, 25, 113, 205, 236, 245, 211, 219, 9, 169, 202, 229, 188, 222, 147, 159, 178, 217, 11, 28, 10, 26, 125, 16, 91, 184, 110, 239, 101, 193, 120, 173, 254, 19, 54, 145, 90, 6, 197, 108, 129, 89, 41, 34, 214, 27, 134, 107, 43, 106, 46, 209, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    UJavaRandom* random = NewObject<UJavaRandom>();
    random->SetSeed(1);
    USimplexNoiseGenerator* generator = NewObject<USimplexNoiseGenerator>();
    generator->Init(*random);

    TestEqual("xo", generator->m_xo, expectedXO);
    TestEqual("yo", generator->m_yo, expectedYO);
    TestEqual("zo", generator->m_yo, expectedYO);

    for(int i = 0; i < NUM_RANDOMS; ++i)
    {
        TestEqual(TEXT("Random Value #") + FString::FromInt(i + 1), generator->m_randoms[i], expectedRandoms[i]);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSimplexNoiseGeneratorTestGetValue2d, "MC_UE4.World.Gen.SimplexNoiseGenerator Test Result of GetValue in 2 dimensions", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FSimplexNoiseGeneratorTestGetValue2d::RunTest(const FString& Parameters)
{
    const int NUM_RESULTS = 3;
    double expectedResults[] = {
        0.37133235352606553,
        0.043680041988801134,
        0.00437493000042
    };

    UJavaRandom* random = NewObject<UJavaRandom>();
    random->SetSeed(1);
    USimplexNoiseGenerator* gen = NewObject<USimplexNoiseGenerator>();
    gen->Init(*random);

    double results[] = {
        gen->GetValue(0.1, 0.1),
        gen->GetValue(0.01, 0.01),
        gen->GetValue(0.001, 0.001)
    };

    for (int i = 0; i < NUM_RESULTS; ++i)
    {
        TestEqual(TEXT("GetValue Result #") + FString::FromInt(i + 1), results[i], expectedResults[i]);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSimplexNoiseGeneratorTestGetValue3d, "MC_UE4.World.Gen.SimplexNoiseGenerator Test Result of GetValue in 3 dimensions", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FSimplexNoiseGeneratorTestGetValue3d::RunTest(const FString& Parameters)
{
    const int NUM_RESULTS = 3;
    double expectedResults[] = {
        0.6755840639999999,
        0.0827782363745332,
        0.00829423411324415
    };

    UJavaRandom* random = NewObject<UJavaRandom>();
    random->SetSeed(1);
    USimplexNoiseGenerator* gen = NewObject<USimplexNoiseGenerator>();
    gen->Init(*random);
    
    double results[] = {
        gen->GetValue(0.1, 0.1, 0.1),
        gen->GetValue(0.01, 0.01, 0.01),
        gen->GetValue(0.001, 0.001, 0.001)
    };

    for(int i = 0; i < NUM_RESULTS; ++i)
    {
        TestEqual(TEXT("GetValue Result #") + FString::FromInt(i + 1), results[i], expectedResults[i]);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSimplexNoiseGeneratorTestProcessGrad, "MC_UE4.World.Gen.SimplexNoiseGenerator Test Result of ProcessGrad", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FSimplexNoiseGeneratorTestProcessGrad::RunTest(const FString& Parameters)
{
    double expectedResult = 9.0;

    int8_t grads[3] = { 0, 1, 2 };
    double result = USimplexNoiseGenerator::ProcessGrad(
        grads,
        3.0,
        3.0,
        3.0
    );

    TestEqual("Result of ProcessGrad", result, expectedResult);

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSimplexNoiseGeneratorTestGetPermutValue, "MC_UE4.World.Gen.SimplexNoiseGenerator Test Result of GetPermutValue", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FSimplexNoiseGeneratorTestGetPermutValue::RunTest(const FString& Parameters)
{
    int expectedResult = 62;

    UJavaRandom* random = NewObject<UJavaRandom>();
    random->SetSeed(1);
    USimplexNoiseGenerator* gen = NewObject<USimplexNoiseGenerator>();
    gen->Init(*random);
    int result = gen->GetPermutValue(3);

    TestEqual("Result of GetPermutValue", result, expectedResult);

    return true;
}