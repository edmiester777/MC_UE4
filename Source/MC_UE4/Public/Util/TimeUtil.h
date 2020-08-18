#pragma once
#include "CoreMinimal.h"

class TimeUtil
{
public:
    /**
     * @brief Get the current nanoseconds since ephoch.
     * 
     * @return uint64_t Number of nanoseconds since epoch.
     */
    static uint64_t NanoTime();
};

