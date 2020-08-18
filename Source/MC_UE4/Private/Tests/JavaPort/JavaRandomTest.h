#pragma once

#include <jni.h>
#include <JavaPort/JavaRandom.h>

/**
 * @brief 
 * 
 * @param seed Seed for this random
 * @param[out] jrandomCls Class in JVM for java.util.Random
 * @param[out] jrandom Constructed object
 */
void InitJavaRandomJVM(
    long seed,
    jclass& jrandomCls,
    jobject& jrandom
);

/**
 * @brief Initialize a UJavaRandom (helper function)
 * 
 * @param seed Seed for the random.
 * @return UJavaRandom* 
 */
UJavaRandom* InitJavaRandom(long seed);