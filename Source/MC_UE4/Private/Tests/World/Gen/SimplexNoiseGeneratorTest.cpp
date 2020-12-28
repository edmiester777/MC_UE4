#include "SimplexNoiseGeneratorTest.h"
#include <Tests/JavaPort/JavaRandomTest.h>

#define NUM_SAMPLES 1000

void InitSimplexNoiseGeneratorJVM(long seed, jclass& jgenCls, jobject& jgenerator)
{
    // getting jvm environment
    JNIEnv* env = JavaTestUtil::Instance()->GetEnv();

    // getting JVM definitions
    jclass jrandomCls;
    jobject jrandom;
    InitJavaRandomJVM(seed, jrandomCls, jrandom);
    jgenCls = env->FindClass("net/minecraft/world/gen/SimplexNoiseGenerator");
    jmethodID genCtor = env->GetMethodID(jgenCls, "<init>", "(Ljava/util/Random;)V");

    // constructing noise generator
    jgenerator = env->NewObject(jgenCls, genCtor, jrandom);
}

USimplexNoiseGenerator* InitSimplexNoiseGenerator(long seed)
{
    UJavaRandom* random = InitJavaRandom(seed);
    USimplexNoiseGenerator* gen = NewObject<USimplexNoiseGenerator>();
    gen->Init(*random);
    return gen;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSimplexNoiseGeneratorTestInit, "MC_UE4.World.Gen.SimplexNoiseGenerator.Initialization of Simplex Noise Generator.", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FSimplexNoiseGeneratorTestInit::RunTest(const FString& Parameters)
{
    // setting up environment
    JNI_CLEAR_ERROR;
    JNIEnv* env = JavaTestUtil::Instance()->GetEnv();

    for(int i = 0; i < NUM_SAMPLES; ++i)
    {
        // generating a random seed
        int seed = rand();

        // constructing java and c++ versions
        jclass jgenCls;
        jobject jgen;
        InitSimplexNoiseGeneratorJVM(seed, jgenCls, jgen);
        USimplexNoiseGenerator* gen = InitSimplexNoiseGenerator(seed);

        JNI_TEST_CHECK_AND_PRINT_ERROR;

        // Getting links to fields
        jfieldID jxoField = env->GetFieldID(jgenCls, "xo", "D");
        jfieldID jyoField = env->GetFieldID(jgenCls, "yo", "D");
        jfieldID jzoField = env->GetFieldID(jgenCls, "zo", "D");
        jfieldID jRandomsField = env->GetFieldID(jgenCls, "p", "[I");
        jfieldID jF2Field = env->GetStaticFieldID(jgenCls, "F2", "D");
        jfieldID jG2Field = env->GetStaticFieldID(jgenCls, "G2", "D");

        // getting values from java class
        double jxo = env->GetDoubleField(jgen, jxoField);
        double jyo = env->GetDoubleField(jgen, jyoField);
        double jzo = env->GetDoubleField(jgen, jzoField);
        double jf2 = env->GetStaticDoubleField(jgenCls, jF2Field);
        double jg2 = env->GetStaticDoubleField(jgenCls, jG2Field);
        jintArray jRandoms = (jintArray)env->GetObjectField(jgen, jRandomsField);
        jint* jRandomsValue = env->GetIntArrayElements(jRandoms, NULL);

        // testing likeness
        TestEqual(FString::Printf(TEXT("Sample %i XO"), i), gen->m_xo, jxo);
        TestEqual(FString::Printf(TEXT("Sample %i YO"), i), gen->m_yo, jyo);
        TestEqual(FString::Printf(TEXT("Sample %i ZO"), i), gen->m_zo, jzo);
        TestEqual(FString::Printf(TEXT("Sample %i F2"), i), gen->F2, jf2);
        TestEqual(FString::Printf(TEXT("Sample %i G2"), i), gen->G2, jg2);
        for(int j = 0; j < env->GetArrayLength(jRandoms); ++j)
        {
            TestEqual(FString::Printf(TEXT("Random value index %i"), j), gen->m_permutations[j], (int)(jRandomsValue[j]));
        }

        // cleaning up
        env->ReleaseIntArrayElements(jRandoms, jRandomsValue, 0);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSimplexNoiseGeneratorTestGetValue2d, "MC_UE4.World.Gen.SimplexNoiseGenerator.GetValue in 2 dimensions", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FSimplexNoiseGeneratorTestGetValue2d::RunTest(const FString& Parameters)
{
    // getting JVM environment
    JNI_CLEAR_ERROR;
    JNIEnv* env = JavaTestUtil::Instance()->GetEnv();

    // performing a number of samples
    for(int i = 0; i < NUM_SAMPLES; ++i)
    {
        // generating seed
        int seed = rand();

        // constructing objects
        jclass jgenCls;
        jobject jgen;
        InitSimplexNoiseGeneratorJVM(seed, jgenCls, jgen);
        jmethodID jgetValue = env->GetMethodID(jgenCls, "getValue", "(DD)D");
        USimplexNoiseGenerator* gen = InitSimplexNoiseGenerator(seed);

        JNI_TEST_CHECK_AND_PRINT_ERROR;

        // getting values
        double x = (double)rand();
        double y = (double)rand();
        double jresult = env->CallDoubleMethod(jgen, jgetValue, x, y);
        double result = gen->GetValue(x, y);

        JNI_TEST_CHECK_AND_PRINT_ERROR;

        FString message = FString::Printf(TEXT("Result seed=%i, x=%f, y=%f"), seed, x, y);
        TestEqual(message, result, jresult);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSimplexNoiseGeneratorTestGetValue3d, "MC_UE4.World.Gen.SimplexNoiseGenerator.GetValue in 3 dimensions", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSimplexNoiseGeneratorTestProcessGrad, "MC_UE4.World.Gen.SimplexNoiseGenerator.ProcessGrad", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSimplexNoiseGeneratorTestGetContrib, "MC_UE4.World.Gen.SimplexNoiseGenerator.GetContrib", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FSimplexNoiseGeneratorTestGetContrib::RunTest(const FString& Parameters)
{
    // getting JVM environment
    JNIEnv* env = JavaTestUtil::Instance()->GetEnv();

    // performing a number of samples
    for (int i = 0; i < NUM_SAMPLES; ++i)
    {
        // generating seed
        int seed = rand();

        // constructing objects
        jclass jgenCls;
        jobject jgen;
        InitSimplexNoiseGeneratorJVM(seed, jgenCls, jgen);
        jmethodID jgetContrib = env->GetMethodID(jgenCls, "getContrib", "(IDDDD)D");
        USimplexNoiseGenerator* gen = InitSimplexNoiseGenerator(seed);

        // getting values
        int gradIndex = rand();
        double x = FMath::RandRange(0.0f, 100000000.0f);
        double y = FMath::RandRange(0.0f, 100000000.0f);
        double z = FMath::RandRange(0.0f, 100000000.0f);
        double offset = FMath::RandRange(0.0f, 100000000.0f);
        
        double jresult = env->CallDoubleMethod(jgen, jgetContrib, gradIndex, x, y, z, offset);
        double result = gen->GetContrib(gradIndex, x, y, z, offset);

        FString message = FString::Printf(TEXT("Result seed=%i, gradIndex=%i, x=%f, y=%f, z=%f, offset=%f"), seed, gradIndex, x, y, z, offset);
        TestEqual(message, result, jresult);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSimplexNoiseGeneratorTestGetPermutValue, "MC_UE4.World.Gen.SimplexNoiseGenerator.GetPermutValue", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FSimplexNoiseGeneratorTestGetPermutValue::RunTest(const FString& Parameters)
{
    // getting JVM environment
    JNIEnv* env = JavaTestUtil::Instance()->GetEnv();

    // performing a number of samples
    for (int i = 0; i < NUM_SAMPLES; ++i)
    {
        // generating seed
        int seed = rand();

        // constructing objects
        jclass jgenCls;
        jobject jgen;
        InitSimplexNoiseGeneratorJVM(seed, jgenCls, jgen);
        jmethodID jgetPermutValue = env->GetMethodID(jgenCls, "getPermutValue", "(I)I");
        USimplexNoiseGenerator* gen = InitSimplexNoiseGenerator(seed);

        for(int j = 0; j < 10; ++j)
        {
            // getting values
            int permutIndex = rand();

            int jresult = env->CallIntMethod(jgen, jgetPermutValue, permutIndex);
            int result = gen->GetPermutValue(permutIndex);

            FString message = FString::Printf(TEXT("Result seed=%i, permutIndex=%i"), seed, permutIndex);
            TestEqual(message, result, jresult);
        }
    }

    return true;
}