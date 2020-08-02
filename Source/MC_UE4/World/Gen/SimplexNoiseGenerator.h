// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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
public:
	UPROPERTY()
	double xo;
	double yo;
	double zo;
private:
	int **m_gradients;
	const double F2 = 0.5 * (__SIMPLEX_SQRT_3 - 1.0);
	const double G2 = (3.0 - __SIMPLEX_SQRT_3) / 6.0;
	int m_randoms[512];

public:
	USimplexNoiseGenerator();
	void init(FRandomStream &seed);

private:
	int getPermutValue(int permutIndex);
};
