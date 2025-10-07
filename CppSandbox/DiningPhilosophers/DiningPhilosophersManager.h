#pragma once
#include <memory>
#include <vector>

#include "Fork.h"
#include "Philosopher.h"

namespace DiningPhilosophers
{
    class DiningPhilosophersManager
    {
    public:
        DiningPhilosophersManager(int philosophersCount)
        {
            for (int i = 0; i < philosophersCount; ++i)
            {
                std::unique_ptr<Philosopher> philosopher = std::make_unique<Philosopher>();
                std::unique_ptr<Fork> fork = std::make_unique<Fork>();

                philosophers.push_back(std::move(philosopher));
                forks.push_back(std::move(fork));
            }
        }

    private:
        std::vector<std::unique_ptr<Philosopher>> philosophers;
        std::vector<std::unique_ptr<Fork>> forks;
    };
}
