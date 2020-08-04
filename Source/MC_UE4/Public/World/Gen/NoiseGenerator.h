#pragma once

#include "CoreMinimal.h"
#include "NoiseGenerator.generated.h"

/**
 * Base class for noise generators.
 */
UCLASS()
class UNoiseGenerator : public UObject
{
    GENERATED_BODY()

public:
    virtual double NoiseAt(double x, double y, double z, double multiplier);
};