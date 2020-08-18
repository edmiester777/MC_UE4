// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../JavaPort/JavaRandom.h"
#include "SimplexNoiseGenerator.generated.h"

#define __SIMPLEX_SQRT_3 ((double)1.73205080757)

/**
 * An implementation of the SimplexNoiseGenerator for use in Unreal Engine.
 * 
 * Original source found in net.minecraft.world.gen.SimplexNoiseGenerator
 */
UCLASS()
class MC_UE4_API USimplexNoiseGenerator : public UObject
{
	GENERATED_BODY()
private:
	const int8_t m_gradients[16][3] = {
		{1, 1, 0},
		{-1, 1, 0},
		{1, -1, 0},
		{-1, -1, 0},
		{1, 0, 1},
		{-1, 0, 1},
		{1, 0, -1},
		{-1, 0, -1},
		{0, 1, 1},
		{0, -1, 1},
		{0, 1, -1},
		{0, -1, -1},
		{1, 1, 0},
		{0, -1, 1},
		{-1, 1, 0},
		{0, -1, -1}
	};
	const double F2 = 0.5 * (__SIMPLEX_SQRT_3 - 1.0);
	const double G2 = (3.0 - __SIMPLEX_SQRT_3) / 6.0;
	int32_t m_permutations[512];
	double m_xo;
	double m_yo;
	double m_zo;

public:
	USimplexNoiseGenerator();

	/**
	 * @brief Get the XO value for this generator.
	 * 
	 * @return double 
	 */
	double XO();

	/**
	 * @brief Get the YO value for this generator.
	 * 
	 * @return double 
	 */
	double YO();

	/**
	 * @brief Get the ZO value for this generator.
	 * 
	 * @return double 
	 */
	double ZO();

	/**
	 * @brief Initialize this generator with a seed.
	 *
	 * Perform the initialization step for this generator with a given seed.
	 *
	 * @param seed Seed used to initialize.
	 */
	void Init(UJavaRandom& seed);

	/**
	 * @brief Get noise value for two dimensional coordinate.
	 * 
	 * @param x X coordinate.
	 * @param y Y coordinate.
	 * @return double Value betweeen 0 and 1.
	 */
	double GetValue(double x, double y);

	/**
	 * @brief Get noise value for three dimensional coordinate.
	 *
	 * See https://en.wikipedia.org/wiki/Simplex_noise for more information on the
	 * purpose of this function.
	 *
	 * @param x X coordinate.
	 * @param y Y coordinate.
	 * @param z Z coordinate.
	 * @return double Value between 0 and 1.
	 */
	double GetValue(double x, double y, double z);

protected:
	/**
	 * Process a gradient.
	 *
	 * @param gradElement Gradient values to use.
	 * @param xFactor X factor to be processed with corresponding gradient.
	 * @param yFactor Y factor to be processed with corresponding gradient.
	 * @param zFactor Z factor to be processed with corresponding gradient.
	 * @return double
	 */
	static double ProcessGrad(
		const int8_t gradElement[3],
		double xFactor,
		double yFactor,
		double zFactor
	);

private:
	int GetPermutValue(int permutIndex);
	double GetContrib(int gradIndex, double x, double y, double z, double offset);

	friend class FSimplexNoiseGeneratorTestInit;
	friend class FSimplexNoiseGeneratorTestProcessGrad;
	friend class FSimplexNoiseGeneratorTestGetContrib;
	friend class FSimplexNoiseGeneratorTestGetPermutValue;
};