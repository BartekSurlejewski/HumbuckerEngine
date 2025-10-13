#pragma once
#include <mutex>

namespace DiningPhilosophers
{
    struct Fork
    {
        std::mutex mutex;
    };
}
