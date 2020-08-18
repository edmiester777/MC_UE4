#include "TimeUtil.h"
#include <chrono>

using namespace std::chrono;

uint64_t TimeUtil::NanoTime()
{
    steady_clock::time_point now = high_resolution_clock::now();
    steady_clock::duration duration = now.time_since_epoch();
    uint64_t n = duration_cast<nanoseconds>(duration).count();

    return n;
}
