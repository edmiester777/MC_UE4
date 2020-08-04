#include "PerlinNoiseGenerator.h"
#include <Util/SharedSeedRandom.h>
#include <exception>

using namespace std;

UPerlinNoiseGenerator::UPerlinNoiseGenerator()
{
}

void UPerlinNoiseGenerator::Init(USharedSeedRandom& seed, TArray<int> octaves)
{
    if(octaves.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("UPerlinNoiseGenerator was seeded with no octaves!"));
        return;
    }
    
    // ensuring sort
    octaves.Sort();

    int firstInt = octaves[0];
    int lastInt = octaves.Last();

    int i = firstInt * -1;
    int j = lastInt;
    int k = i + j + 1;

    m_noiseLevels.SetNumZeroed(k);
    if (k < 1)
    {
        throw exception("Total number of octaves needs to be >= 1");
    }
    else
    {
        USimplexNoiseGenerator* noise = NewObject<USimplexNoiseGenerator>(this);
        noise->Init(seed);
        int l = j;

        if(j >= 0 && j < k && octaves.Contains(0))
        {
            m_noiseLevels[j] = noise;
        }

        for(int i1 = j + 1; i1 < k; ++i1)
        {
            if(i1 >= 0 && octaves.Contains(l - i1))
            {
                USimplexNoiseGenerator* noiseLevel = NewObject<USimplexNoiseGenerator>(this);
                noiseLevel->Init(seed);
                m_noiseLevels[i1] = noiseLevel;
            }
            else
            {
                seed.Skip(262);
            }
        }

        if(j > 0)
        {
            int64_t k1 = (int64_t)(noise->GetValue(
                noise->XO(),
                noise->YO(),
                noise->ZO()
            ) * (double)9.223372E18f);

            USharedSeedRandom* ssr = NewObject<USharedSeedRandom>(this);
            ssr->SetSeed(k1);

            for(int j1 = l - 1; j1 >= 0; --j1)
            {
                if (j1 < k && octaves.Contains(l - j1))
                {
                    USimplexNoiseGenerator* noiseLevel = NewObject<USimplexNoiseGenerator>(this);
                    noiseLevel->Init(*ssr);
                    m_noiseLevels[j1] = noiseLevel;
                }
                else
                {
                    ssr->Skip(262);
                }
            }

            m_xo = 1.0 / (pow(2.0, (double)k) - 1.0);
            m_yo = pow(2.0, (double)j);
        }
    }
}

double UPerlinNoiseGenerator::NoiseAt(double x, double y, bool useNoiseOffsets)
{
    double d0 = 0.0;
    double d1 = m_yo;
    double d2 = m_xo;

    for(int i = 0; i < m_noiseLevels.Num(); ++i)
    {
        USimplexNoiseGenerator* gen = m_noiseLevels[i];
        if(gen != nullptr)
        {
            double tmp = gen->GetValue(
                x * d1 + (useNoiseOffsets ? gen->XO() : 0.0),
                y * d1 + (useNoiseOffsets ? gen->YO() : 0.0)
            ) * d2;
            
            d0 += tmp;
        }

        d1 /= 2.0;
        d2 *= 2.0;
    }

    return d0;
}

double UPerlinNoiseGenerator::NoiseAt(double x, double y, double z, double multiplier)
{
    return NoiseAt(x, y, true) * 0.55;
}
