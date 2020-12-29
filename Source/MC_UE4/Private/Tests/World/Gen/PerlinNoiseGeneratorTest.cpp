#include "CoreMinimal.h"
#include <World/Gen/PerlinNoiseGenerator.h>
#include "PerlinNoiseGeneratorTest.h"
#include <Tests/Util/SharedSeedRandomTest.h>
#include <TestUtil/JniListHelper.h>

#define NUM_SAMPLES 5

TArray<int> PerlinNoiseTest_GetIntArr()
{
    TArray<int> arr;

    for (int i = 0; i < 15; ++i)
    {
        arr.Add(rand());
    }

    return arr;
}

void InitPerlinNoiseGeneratorJVM(long seed, TArray<int> octaves, jclass& jgenCls, jobject& jgenerator)
{
    // getting JVM definitions
    jclass ssrCls;
    jobject ssr;
    InitSharedSeedRandomJVM(seed, ssrCls, ssr);
    jgenCls = JNI_ENV->FindClass("net/minecraft/world/gen/PerlinNoiseGenerator");
    jmethodID genCtor = JNI_ENV->GetMethodID(
        jgenCls,
        "<init>",
        "("
            "Lnet/minecraft/util/SharedSeedRandom;"
            "Ljava/util/List;"
        ")V"
    );

    // constructing noise generator
    jobject intList = JniListHelper::ToList(octaves);
    jgenerator = JNI_ENV->NewObject(
        jgenCls,
        genCtor,
        ssr,
        intList
    );
}

UPerlinNoiseGenerator* InitPerlinNoiseGenerator(long seed, TArray<int> octaves)
{
    USharedSeedRandom* ssr = InitSharedSeedRandom(seed);

    UPerlinNoiseGenerator* gen = NewObject<UPerlinNoiseGenerator>();
    gen->Init(*ssr, octaves);

    return gen;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPerlinNoiseGeneratorTestInit, "MC_UE4.World.Gen.PerlinNoiseGenerator.Test Initialization of Perlin Noise Generator.", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FPerlinNoiseGeneratorTestInit::RunTest(const FString& Parameters)
{
    JNI_CLEAR_ERROR;

    const char* clsFieldX = "field_227462_b_";
    const char* clsFieldY = "field_227463_c_";

    long seed = rand();
    TArray<int> ints = PerlinNoiseTest_GetIntArr();

    // setting up JVM objects
    jclass jgenCls;
    jobject jgen;
    InitPerlinNoiseGeneratorJVM(seed, ints, jgenCls, jgen);
    UPerlinNoiseGenerator* gen = InitPerlinNoiseGenerator(seed, ints);
    JNI_TEST_CHECK_AND_PRINT_ERROR;

    // getting fields from java objects
    jfieldID xField = JNI_ENV->GetFieldID(jgenCls, clsFieldX, "D");
    jfieldID yField = JNI_ENV->GetFieldID(jgenCls, clsFieldY, "D");
    double jXVal = JNI_ENV->GetDoubleField(jgen, xField);
    double jYVal = JNI_ENV->GetDoubleField(jgen, yField);

    // asserting
    TestEqual(TEXT("X field not equal."), gen->m_xo, jXVal);
    TestEqual(TEXT("Y field not equal."), gen->m_yo, jYVal);

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPerlinNoiseGeneratorTestNoiseAtXY, "MC_UE4.World.Gen.PerlinNoiseGenerator.Test NoiseAt with XY function.", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FPerlinNoiseGeneratorTestNoiseAtXY::RunTest(const FString& Parameters)
{
    JNI_CLEAR_ERROR;

    for (int i = 0; i < NUM_SAMPLES; ++i)
    {
        // setting up params
        long seed = rand();
        TArray<int> octaves = PerlinNoiseTest_GetIntArr();
        double x = FMath::RandRange(0.0f, 100000000.0f);
        double y = FMath::RandRange(0.0f, 100000000.0f);
        bool useNoiseOffsets = FMath::RandBool();

        // constructing generators
        jclass jgenCls;
        jobject jgen;
        InitPerlinNoiseGeneratorJVM(seed, octaves, jgenCls, jgen);
        UPerlinNoiseGenerator* gen = InitPerlinNoiseGenerator(seed, octaves);
        JNI_TEST_CHECK_AND_PRINT_ERROR;

        // getting relevant method ID
        jmethodID noiseAt = JNI_ENV->GetMethodID(
            jgenCls,
            "noiseAt",
            "(DDZ)D"
        );
        
        // calling functions
        double jval = JNI_ENV->CallDoubleMethod(jgen, noiseAt, (jdouble)x, (jdouble)y, (jboolean)useNoiseOffsets);
        double val = gen->NoiseAt(x, y, useNoiseOffsets);
        JNI_TEST_CHECK_AND_PRINT_ERROR;
        TestEqual(TEXT("Results not equal."), val, jval);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPerlinNoiseGeneratorTestNoiseAtXYZ, "MC_UE4.World.Gen.PerlinNoiseGenerator.Test NoiseAt with XYZ function.", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FPerlinNoiseGeneratorTestNoiseAtXYZ::RunTest(const FString& Parameters)
{
    JNI_CLEAR_ERROR;

    for (int i = 0; i < NUM_SAMPLES; ++i)
    {
        // setting up params
        long seed = rand();
        TArray<int> octaves = PerlinNoiseTest_GetIntArr();
        double x = FMath::RandRange(0.0f, 100000000.0f);
        double y = FMath::RandRange(0.0f, 100000000.0f);
        double z = FMath::RandRange(0.0f, 100000000.0f);

        // constructing generators
        jclass jgenCls;
        jobject jgen;
        InitPerlinNoiseGeneratorJVM(seed, octaves, jgenCls, jgen);
        UPerlinNoiseGenerator* gen = InitPerlinNoiseGenerator(seed, octaves);
        JNI_TEST_CHECK_AND_PRINT_ERROR;

        // getting relevant method ID
        jmethodID noiseAt = JNI_ENV->GetMethodID(
            jgenCls,
            "noiseAt",
            "(DDDD)D"
        );

        // calling functions
        double jval = JNI_ENV->CallDoubleMethod(
            jgen, 
            noiseAt, 
            (jdouble)x, 
            (jdouble)y,
            (jdouble)z,
            (jdouble)0.0
        );
        double val = gen->NoiseAt(x, y, z, 0.0);
        JNI_TEST_CHECK_AND_PRINT_ERROR;
        TestEqual(TEXT("Results not equal."), val, jval);
    }

    return true;
}