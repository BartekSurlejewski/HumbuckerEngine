#pragma once
#include <random>
#include <vector>

class HumbuckerUtils
{
public:
    HumbuckerUtils();
    std::vector<int> SelectionSort(const std::vector<int>& numbersToSort);
    std::vector<int> Quicksort(const std::vector<int>& numbersToSort);

    inline int GetRandomNumber(const int minNumber, const int maxNumber)
    {
        std::uniform_real_distribution<double> dist(minNumber, maxNumber);
        return dist(mersenneTwister);
    }

private:
    std::random_device randomDevice;
    std::mt19937 mersenneTwister;

    /**
     * \brief Returns an index of the smallest number in a vector.
     * Used by selection sort algorithm.
     */
    inline int GetSmallest(const std::vector<int>& numbers) const;
};
