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
    m_seed = InitialScrable(seed);

    // haveNextNextGaussian???
}

int64_t UJavaRandom::InitialScrable(int64_t seed)
{
    return (seed ^ m_multiplier) & m_mask;
}
