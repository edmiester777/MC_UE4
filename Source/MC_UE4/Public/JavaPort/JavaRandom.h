// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JavaRandom.generated.h"

/**
 * @brief A port of the Random class from java.util for use in Unreal.
 *
 * A simple port of the Random class in java. Note that this is not an all-encompassing
 * port and SHOULD be improved later.
 */
UCLASS()
class MC_UE4_API UJavaRandom : public UObject
{
	GENERATED_BODY()

private:
	TAtomic<int64_t> m_seed;
	bool m_haveNextNextGaussian;

	const int64_t m_seedUniquifier = 8682522807148012L;
	const int64_t m_multiplier = 0x5DEECE66DL;
	const int64_t m_addend = 0xBL;
	const int64_t m_mask = (((int64_t)1L) << 48) - 1;
	const double m_double_unit = 1.0 / (((int64_t)1L) << 53);
public:
	UJavaRandom();
	virtual ~UJavaRandom();
	virtual void SetSeed(int64_t seed);
	virtual int32_t Next(int bits);
	virtual int32_t NextInt();
	virtual int32_t NextInt(unsigned int bound);
	virtual double NextDouble();
	virtual int64_t NextLong();

private:
	int64_t InitialScramble(int64_t seed);

	friend class FJavaRandomNextTestPositive1Seed;
	friend class FJavaRandomNextTestNegative1Seed;
};
