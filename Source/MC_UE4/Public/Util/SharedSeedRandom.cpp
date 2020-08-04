#include "SharedSeedRandom.h"

USharedSeedRandom::USharedSeedRandom()
{
    m_usageCount = 0;
}

void USharedSeedRandom::Skip(int bits)
{
    for(int i = 0; i < bits; ++i)
    {
        Next(1);
    }
}

int32_t USharedSeedRandom::Next(int bits)
{
    ++m_usageCount;
    return UJavaRandom::Next(bits);
}

int64_t USharedSeedRandom::SetBaseChunkSeed(int x, int z)
{
    const int64_t X_MULT = 341873128712L;
    const int64_t Z_MULT = 132897987541L;
    int64_t seed = ((int64_t)x * X_MULT) + ((int64_t)z * Z_MULT);
    SetSeed(seed);
    return seed;
}

int64_t USharedSeedRandom::SetDecorationSeed(int64_t baseSeed, int x, int z)
{
    SetSeed(baseSeed);
    int64_t i = NextLong() | 1L;
    int64_t j = NextLong() | 1L;
    int64_t k = ((int64_t)x * i) + ((int64_t)z * j) ^ baseSeed;
    SetSeed(k);
    return k;
}

int64_t USharedSeedRandom::SetFeatureSeed(int64_t baseSeed, int x, int z)
{
    int64_t i = baseSeed + (int64_t)x + (int64_t)(10000 * z);
    SetSeed(i);
    return i;
}

int64_t USharedSeedRandom::SetLargeFeatureSeed(int64_t seed, int x, int z)
{
    SetSeed(seed);
    int64_t i = NextLong();
    int64_t j = NextLong();
    int64_t k = ((int64_t)x * i) ^ ((int64)z * j) ^ seed;
    SetSeed(k);
    return k;
}

int64_t USharedSeedRandom::SetLargeFeatureSeedWithSalt(int64_t baseSeed, int x, int z, int modifier)
{
    const int64_t X_MULT = 341873128712L;
    const int64_t Z_MULT = 132897987541L;
    int64_t i = ((int64_t)x * X_MULT) + ((int64_t)z * Z_MULT) + baseSeed + modifier;
    SetSeed(i);
    return i;
}
