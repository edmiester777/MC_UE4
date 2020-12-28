#pragma once
#include "CoreMinimal.h"
#include <TestUtil/JavaTestUtil.h>
#include <Util/SharedSeedRandom.h>

/**
 * Helper function to initialize the java SharedSeedRandom
 * 
 * @param jRandom Instantiated java random class.
 * @param[out] ssrCls Java class definition of net.minecraft.util.SharedSeedRandom
 * @param[out] ssr Constructed SharedSeedRandom in jvm.
 */
void InitSharedSeedRandomJVM(
    long seed, 
    jclass& ssrCls, 
    jobject& ssr
);

/**
 * @brief Helper function to initialize the C++ simplex noise generator with a seed.
 * 
 * @param seed Seed for the random.
 * @return USimplexNoiseGenerator* 
 */
USharedSeedRandom* InitSharedSeedRandom(long seed);