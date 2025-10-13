#include <iostream>
#include <string>
#include <chrono>
#include <mutex>
#include <thread>
#include <vector>
#include <sstream>

#include "AlgorithmsImplementations.h"

// Takes string and returns it with all words that have at least five letters reversed
static std::string spinWords(const std::string &str)
{
	std::stringstream ss(str);
	std::string result = "";
	std::string word;

	while (ss >> word)
	{
		if (word.length() < 5)
		{
			result += word + " ";
		} else
		{
			std::string revWord = std::string(word.rbegin(), word.rend());
			result += revWord + " ";
		}
	}

	// Remove the last space in the string
	if (result.length() > 0)
	{
		result.pop_back();
	}

	return result;
} // spinWords

int main(int argc, char *argv[])
{
	using namespace std::literals::chrono_literals;

	std::cout << "Hello\n";

	// std::this_thread::sleep_for(1s);


	const auto impl = new AlgorithmsImplementations();
	std::vector<int> numbers;

	for (int i = 0; i < 10000; ++i)
	{
		numbers.push_back(impl->GetRandomNumber(-1000000, 1000000));
	}

	// TODO: implement timer struct
	auto quickSortStartTime = std::chrono::high_resolution_clock::now();

	// Call quicksort on a separate thread
	std::thread quickSortThread(&AlgorithmsImplementations::Quicksort, impl, numbers);

	auto selectionSortStartTime = std::chrono::high_resolution_clock::now();

	// Call selection sort on a separate thread
	std::thread selectionSortThread(&AlgorithmsImplementations::SelectionSort, impl, numbers);

	quickSortThread.join();
	std::chrono::duration<float> quickSortDuration = std::chrono::high_resolution_clock::now() - quickSortStartTime;

	selectionSortThread.join();
	std::chrono::duration<float> selectionSortDuration =
			std::chrono::high_resolution_clock::now() - selectionSortStartTime;

	std::cout << "Quick Sort Duration: " << quickSortDuration.count() * 1000.0 << "ms" << std::endl;
	std::cout << "Selection Sort Duration: " << selectionSortDuration.count() * 1000.0 << "ms" << std::endl;

	std::cout << spinWords("Hey fellow warriors");

	return 0;
}

void Message(std::string message)
{
	static std::mutex coutMutex;
	coutMutex.lock();
	std::cout << message << std::endl;
	coutMutex.unlock();
}
