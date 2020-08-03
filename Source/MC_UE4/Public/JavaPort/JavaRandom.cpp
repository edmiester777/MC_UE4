// Fill out your copyright notice in the Description page of Project Settings.


#include "JavaRandom.h"

UJavaRandom::UJavaRandom()
{
}

UJavaRandom::~UJavaRandom()
{
}

void UJavaRandom::SetSeed(int64_t seed)
{
    m_seed = InitialScramble(seed);

    // haveNextNextGaussian???
}

int64_t UJavaRandom::Next(int bits)
{
    int64_t nextSeed = (m_seed * m_multiplier + m_addend) & m_mask;
    m_seed = nextSeed;
    return nextSeed >> (48 - bits);
}

int32_t UJavaRandom::NextInt()
{
    return Next(32);
}

int32_t UJavaRandom::NextInt(unsigned int bound)
{
    // auto-return if bound is zero to avoid an in-game dick punch
    if (bound == 0)
        return 0;

    int32_t r = Next(31);
    int m = bound - 1;
    if ((bound & m) == 0) // bound is power of two
        return ((bound * (int64_t)r) >> 31);

    for (int u = r; u - (r = u % bound) + m < 0; u = Next(31));
    return r;
}

double UJavaRandom::NextDouble()
{
    uint64_t nextVal = (Next(26) << 27) + (Next(27));
    return nextVal * m_double_unit;
}

int64_t UJavaRandom::InitialScramble(int64_t seed)
{
    return (seed ^ m_multiplier) & m_mask;
}
