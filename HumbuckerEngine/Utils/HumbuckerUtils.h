#pragma once
#include <random>
#include <vector>

class HumbuckerUtils
{
public:
    HumbuckerUtils();
    static std::vector<int> SelectionSort(const std::vector<int>& numbersToSort);
    static std::vector<int> Quicksort(const std::vector<int>& numbersToSort);

    static std::string GetTextFromFile(const std::string& filePath);

    inline static int GetRandomNumber(const int minNumber, const int maxNumber)
    {
        std::random_device randomDevice;
        std::uniform_real_distribution<double> dist(minNumber, maxNumber);
        std::mt19937 mersenneTwister = std::mt19937(randomDevice());
        return dist(mersenneTwister);
    }

private:
    /**
     * \brief Returns an index of the smallest number in a vector.
     * Used by selection sort algorithm.
     */
    inline static int GetSmallest(const std::vector<int>& numbers);
};
