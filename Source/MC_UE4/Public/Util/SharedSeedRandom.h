#pragma once

#include "CoreMinimal.h"
#include <JavaPort/JavaRandom.h>
#include "UObject/NoExportTypes.h"
#include "SharedSeedRandom.generated.h"

/**
 * A port of net.minecraft.util.SharedSeedRandom for the unreal ecosystem.
 */
UCLASS()
class MC_UE4_API USharedSeedRandom : public UJavaRandom
{
	GENERATED_BODY()
	
private:
	int m_usageCount;

public:
	USharedSeedRandom();

	virtual void Skip(int bits);
	virtual int32_t Next(int bits) override;
	virtual int64_t SetBaseChunkSeed(int x, int z);
	virtual int64_t SetDecorationSeed(int64_t baseSeed, int x, int z);
	virtual int64_t SetFeatureSeed(int64_t baseSeed, int x, int z);
	virtual int64_t SetLargeFeatureSeed(int64_t seed, int x, int z);
	virtual int64_t SetLargeFeatureSeedWithSalt(int64_t baseSeed, int x, int z, int modifier);
};
