// Fill out your copyright notice in the Description page of Project Settings.


#include "SimplexNoiseGenerator.h"

USimplexNoiseGenerator::USimplexNoiseGenerator()
{
    // default gradients.
    const int gradients[16][3] = {
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
    m_gradients = (int**)gradients;
}

void USimplexNoiseGenerator::Init(UJavaRandom &seed)
{
}

int USimplexNoiseGenerator::getPermutValue(int permutIndex)
{
    return m_randoms[permutIndex & 255];
}
