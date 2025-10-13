#include "Philosopher.h"

#include <iostream>
#include <ostream>

void DiningPhilosophers::Philosopher::PickUpFork(Fork* fork)
{
    if (pickedUpForks.size() >= 2)
    {
        // This philosopher has already picked up two forks
        return;
    }

    if (pickedUpForks.find(fork) != pickedUpForks.end())
    {
        // This fork has already been picked up by this philosopher
        return;
    }

    pickedUpForks.insert(fork);
}

void DiningPhilosophers::Philosopher::PutDownFork(Fork* fork)
{
    if (pickedUpForks.find(fork) == pickedUpForks.end())
    {
        // This fork isn't held by this philosopher
        return;
    }

    pickedUpForks.erase(fork);
}

void DiningPhilosophers::Philosopher::Consume()
{
    if (pickedUpForks.size() < 2)
    {
        // Too few forks :(
        return;
    }

    std::cout << "Konsumuję lubieżnie całkiem niezły posiłek\n";
}
