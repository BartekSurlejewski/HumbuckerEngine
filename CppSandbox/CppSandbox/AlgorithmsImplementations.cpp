#include "AlgorithmsImplementations.h"

#include <iostream>
#include <list>

AlgorithmsImplementations::AlgorithmsImplementations()
{
    mersenneTwister = std::mt19937(randomDevice());
}

std::vector<int> AlgorithmsImplementations::SelectionSort(const std::vector<int>& numbersToSort)
{
    int numbersCount = numbersToSort.size();
    std::vector<int> numbersToSortCopy(numbersToSort);
    std::vector<int> sortedVector(numbersCount);

    std::list<int> numbersToSortList;
    std::copy(numbersToSort.begin(), numbersToSort.end(), std::back_inserter(numbersToSortList));

    int smallestNumberIndex;
    for(int i = 0; i < numbersCount; ++i)
    {
        smallestNumberIndex = GetSmallest(numbersToSortCopy);
        sortedVector[i] = numbersToSortCopy[smallestNumberIndex];
        numbersToSortCopy.erase(numbersToSortCopy.begin() + smallestNumberIndex);
    }
    
    return sortedVector;
}

std::vector<int> AlgorithmsImplementations::Quicksort(const std::vector<int>& numbersToSort)
{
    int numbersAmount = numbersToSort.size();
    if (numbersAmount < 2)
    {
        return numbersToSort;
    }

    int pivotIndex = GetRandomNumber(0, numbersAmount - 1);
    int pivot = numbersToSort[pivotIndex];

    std::vector<int> less;
    std::vector<int> greater;

    int equalCount = 0;

    for (int number : numbersToSort)
    {
        if (number < pivot)
        {
            less.push_back(number);
        }
        else if (number > pivot)
        {
            greater.push_back(number);
        }
        else if(number == pivot)
        {
            equalCount++;
        }
    }
    std::vector<int> sortedLess = Quicksort(less);
    std::vector<int> sortedGreater = Quicksort(greater);

    std::vector<int> result;
    result.insert(result.end(), sortedLess.begin(), sortedLess.end());
    result.insert(result.end(), equalCount, pivot);
    result.insert(result.end(), sortedGreater.begin(), sortedGreater.end());
    
    return result;
}

int AlgorithmsImplementations::GetSmallest(const std::vector<int>& numbers) const
{
    int smallestNumberIndex = 0;
    for (int i = 1; i < numbers.size(); ++i)
    {
        if(numbers[i] < numbers[smallestNumberIndex])
        {
            smallestNumberIndex = i;
        }
    }

    return smallestNumberIndex;
}
