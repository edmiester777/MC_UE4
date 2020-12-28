#pragma once
#include "CoreMinimal.h"
#include <TestUtil/JavaTestUtil.h>
#include <World/Gen/SimplexNoiseGenerator.h>

/**
 * Helper function to initialize the java simplex noise generator.
 * 
 * @param jRandom Instantiated java random class.
 * @param[out] genCls Java class definition of net.minecraft.world.gen.SimplexNoiseGenerator
 * @param[out] generator Constructed SimplexNoiseGenerator in jvm.
 */
void InitSimplexNoiseGeneratorJVM(
    long seed, 
    jclass& jgenCls, 
    jobject& jgenerator
);

/**
 * @brief Helper function to initialize the C++ simplex noise generator with a seed.
 * 
 * @param seed Seed for the random.
 * @return USimplexNoiseGenerator* 
 */
USimplexNoiseGenerator* InitSimplexNoiseGenerator(long seed);