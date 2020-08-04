#pragma once

#include "CoreMinimal.h"
#include "NoiseGenerator.h"
#include <Util/SharedSeedRandom.h>
#include "SimplexNoiseGenerator.h"
#include "PerlinNoiseGenerator.generated.h"

typedef TArray<USimplexNoiseGenerator*> SimplexGeneratorList;

/**
 * Perlin Noise generator used for biome generation.
 */
UCLASS()
class MC_UE4_API UPerlinNoiseGenerator : public UNoiseGenerator
{
	GENERATED_BODY()
private:
	SimplexGeneratorList m_noiseLevels;
	double m_xo;
	double m_yo;

public:
	UPerlinNoiseGenerator();
	void Init(USharedSeedRandom& seed, TArray<int> octaves);
	virtual double NoiseAt(double x, double y, bool useNoiseOffsets);
	virtual double NoiseAt(double x, double y, double z, double multiplier) override;

	friend class FPerlinNoiseGeneratorTestInit;
};
