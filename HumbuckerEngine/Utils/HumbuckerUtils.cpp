#include "HumbuckerUtils.h"

#include <fstream>
#include <iostream>
#include <list>
#include <mutex>
#include <sstream>

void ThreadSafeMessage(std::string message)
{
	static std::mutex coutMutex;
	coutMutex.lock();
	std::cout << message << std::endl;
	coutMutex.unlock();
}

std::vector<int> HumbuckerUtils::SelectionSort(const std::vector<int> &numbersToSort)
{
	int numbersCount = numbersToSort.size();
	std::vector<int> numbersToSortCopy(numbersToSort);
	std::vector<int> sortedVector(numbersCount);

	std::list<int> numbersToSortList;
	std::copy(numbersToSort.begin(), numbersToSort.end(), std::back_inserter(numbersToSortList));

	int smallestNumberIndex;
	for (int i = 0; i < numbersCount; ++i)
	{
		smallestNumberIndex = GetSmallest(numbersToSortCopy);
		sortedVector[i] = numbersToSortCopy[smallestNumberIndex];
		numbersToSortCopy.erase(numbersToSortCopy.begin() + smallestNumberIndex);
	}

	return sortedVector;
}

std::vector<int> HumbuckerUtils::Quicksort(const std::vector<int> &numbersToSort)
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

	for (int number: numbersToSort)
	{
		if (number < pivot)
		{
			less.push_back(number);
		}
		else if (number > pivot)
		{
			greater.push_back(number);
		}
		else if (number == pivot)
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

std::string HumbuckerUtils::GetTextFromFile(const std::string &filePath)
{
	std::string fileText;
	std::ifstream file;

	// Ensure the filestream can throw exceptions
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		file.open(filePath);
		std::stringstream stringStream;

		stringStream << file.rdbuf();
		file.close();
		fileText = stringStream.str();
		std::cout << "File read successfully " << filePath << std::endl;
	}
	catch (std::ifstream::failure exception)
	{
		std::cout << "Failed to read file " << filePath << std::endl << "Exception: " << exception.what() << std::endl;
	}
	return fileText;
}

int HumbuckerUtils::GetSmallest(const std::vector<int> &numbers)
{
	int smallestNumberIndex = 0;
	for (int i = 1; i < numbers.size(); ++i)
	{
		if (numbers[i] < numbers[smallestNumberIndex])
		{
			smallestNumberIndex = i;
		}
	}

	return smallestNumberIndex;
}
