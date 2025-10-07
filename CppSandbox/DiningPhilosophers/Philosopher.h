#pragma once
#include <unordered_set>
#include "Fork.h"

namespace DiningPhilosophers
{
    class Philosopher
    {
    public:
        void PickUpFork(Fork* fork);
        void PutDownFork(Fork* fork);
        void Consume();

    private:
        std::unordered_set<Fork*> pickedUpForks;
        bool hasEaten = false;
    };
}
