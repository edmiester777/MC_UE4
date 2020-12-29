#pragma once
#include "CoreMinimal.h"
#include <TestUtil/JavaTestUtil.h>
#include <World/Gen/PerlinNoiseGenerator.h>

/**
 * Helper function to initialize the java perlin noise generator.
 * 
 * @param jRandom Instantiated java random class.
 * @param octaves Octaves to pass to the noise generator.
 * @param[out] genCls Java class definition of net.minecraft.world.gen.PerlinNoiseGenerator
 * @param[out] generator Constructed PerlinNoiseGenerator in jvm.
 */
void InitPerlinNoiseGeneratorJVM(
    long seed, 
    TArray<int> octaves,
    jclass& jgenCls, 
    jobject& jgenerator
);

/**
 * @brief Helper function to initialize the C++ perlin noise generator with a seed.
 * 
 * @param seed Seed for the random.
 * @param octaves Octaves to pass to the noise generator.
 * @return UPerlinNoiseGenerator* 
 */
UPerlinNoiseGenerator* InitPerlinNoiseGenerator(long seed, TArray<int> octaves);