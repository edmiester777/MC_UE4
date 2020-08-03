// Fill out your copyright notice in the Description page of Project Settings.


#include "SimplexNoiseGenerator.h"

USimplexNoiseGenerator::USimplexNoiseGenerator()
{
}

void USimplexNoiseGenerator::Init(UJavaRandom &seed)
{
    m_xo = seed.NextDouble() * 256.0;
    m_yo = seed.NextDouble() * 256.0;
    m_zo = seed.NextDouble() * 256.0;

    for (int i = 0; i < 256; m_randoms[i] = i++);

    // shuffling randoms
    for(int l = 0; l < 256; ++l)
    {
        uint32_t j = seed.NextInt(256 - l);
        uint32_t k = m_randoms[l];
        m_randoms[l] = m_randoms[j + l];
        m_randoms[j + l] = k;
    }
}

double USimplexNoiseGenerator::GetValue(double x, double y)
{
    double d0 = (x + y) * F2;

    double i = FMath::FloorToDouble(x + d0);
    double j = FMath::FloorToDouble(y + d0);

    double d1 = (i + j) * G2;
    double d2 = i - d1;
    double d3 = j - d1;
    double d4 = x - d2;
    double d5 = y - d3;

    int k, l;
    if(d4 > d5)
    {
        k = 1;
        l = 0;
    }
    else
    {
        k = 0;
        l = 1;
    }

    double d6 = d4 - (double)k + G2;
    double d7 = d5 - (double)l + G2;
    double d8 = d4 - 1.0 + 2.0 * G2;
    double d9 = d5 - 1.0 + 2.0 * G2;

    int i1 = (int)i & 0xff;
    int j1 = (int)j & 0xff;

    int k1 = GetPermutValue(i1 + GetPermutValue(j1)) % 12;
    int l1 = GetPermutValue(i1 + k + GetPermutValue(j1 + l)) % 12;
    int i2 = GetPermutValue(i1 + 1 + GetPermutValue(j1 + 1)) % 12;

    double d10 = GetContrib(k1, d4, d5, 0.0, 0.5);
    double d11 = GetContrib(l1, d6, d7, 0.0, 0.5);
    double d12 = GetContrib(i2, d8, d9, 0.0, 0.5);

    return 70.0 * (d10 + d11 + d12);
}

double USimplexNoiseGenerator::GetValue(double x, double y, double z)
{
    double d1 = (x + y + z) * 0.3333333333333333;
    double i = FMath::FloorToDouble(x + d1);
    double j = FMath::FloorToDouble(y + d1);
    double k = FMath::FloorToDouble(z + d1);
    double d3 = (i + j + k) * 0.16666666666666666;
    double d4 = i - d3;
    double d5 = j - d3;
    double d6 = k - d3;
    double d7 = x - d4;
    double d8 = y - d5;
    double d9 = z - d6;

    int l, i1, j1, k1, l1, i2;
    if (d7 >= d8)
    {
        if (d8 >= d9)
        {
            l = 1;
            i1 = 0;
            j1 = 0;
            k1 = 1;
            l1 = 1;
            i2 = 0;
        }
        else if (d7 >= d9)
        {
            l = 1;
            i1 = 0;
            j1 = 0;
            k1 = 1;
            l1 = 0;
            i2 = 1;
        }
        else
        {
            l = 0;
            i1 = 0;
            j1 = 1;
            k1 = 1;
            l1 = 0;
            i2 = 1;
        }
    }
    else if (d8 < d9)
    {
        l = 0;
        i1 = 0;
        j1 = 1;
        k1 = 0;
        l1 = 1;
        i2 = 1;
    }
    else if (d7 < d9)
    {
        l = 0;
        i1 = 1;
        j1 = 0;
        k1 = 0;
        l1 = 1;
        i2 = 1;
    }
    else
    {
        l = 0;
        i1 = 1;
        j1 = 0;
        k1 = 1;
        l1 = 1;
        i2 = 0;
    }

    double d10 = d7 - l + 0.16666666666666666;
    double d11 = d8 - i1 + 0.16666666666666666;
    double d12 = d9 - j1 + 0.16666666666666666;
    double d13 = d7 - k1 + 0.3333333333333333;
    double d14 = d8 - l1 + 0.3333333333333333;
    double d15 = d9 - i2 + 0.3333333333333333;
    double d16 = d7 - 0.5;
    double d17 = d8 - 0.5;
    double d18 = d9 - 0.5;

    int j2 = (int)i & 0xff;
    int k2 = (int)j & 0xff;
    int l2 = (int)k & 0xff;

    int i3 = GetPermutValue(j2 + GetPermutValue(k2 + GetPermutValue(l2))) % 12;
    int j3 = GetPermutValue(j2 + l + GetPermutValue(k2 + i1 + GetPermutValue(l2 + j1))) % 12;
    int k3 = GetPermutValue(j2 + k1 + GetPermutValue(k2 + l1 + GetPermutValue(l2 + i2))) % 12;
    int l3 = GetPermutValue(j2 + 1 + GetPermutValue(k2 + 1 + GetPermutValue(l2 + 1))) % 12;

    double d19 = GetContrib(i3, d7, d8, d9, 0.6);
    double d20 = GetContrib(j3, d10, d11, d12, 0.6);
    double d21 = GetContrib(k3, d13, d14, d15, 0.6);
    double d22 = GetContrib(l3, d16, d17, d18, 0.6);

    return 32.0 * (d19 + d20 + d21 + d22);
}

double USimplexNoiseGenerator::ProcessGrad(
    const int8_t gradElement[3], 
    double xFactor, 
    double yFactor, 
    double zFactor
) {
    return
        (gradElement[0] * xFactor) +
        (gradElement[1] * yFactor) +
        (gradElement[2] * zFactor);
}

int USimplexNoiseGenerator::GetPermutValue(int permutIndex)
{
    return m_randoms[permutIndex & 255];
}

double USimplexNoiseGenerator::GetContrib(int gradIndex, double x, double y, double z, double offset)
{
    double d1 =
        offset -
        (x * x) -
        (y * y) -
        (z * z);
    if (d1 < 0)
        return 0.0;

    d1 *= d1;
    return d1 * d1 * ProcessGrad(m_gradients[gradIndex], x, y, z);
}
