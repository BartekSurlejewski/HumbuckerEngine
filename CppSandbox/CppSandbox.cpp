#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>

#include "AlgorithmsImplementations.h"

int main(int argc, char* argv[])
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
    auto start = std::chrono::high_resolution_clock::now();
    // std::vector<int> sortedNumbersQuicksort = impl->Quicksort(numbers);

    // Call quicksort on a separate thread
    std::thread quickSortThread(&AlgorithmsImplementations::Quicksort, impl, numbers);

    start = std::chrono::high_resolution_clock::now();
    // std::vector<int> sortedNumbersSelectionSort = impl->SelectionSort(numbers);

    // Call selection sort on a separate thread
    std::thread selectionSortThread(&AlgorithmsImplementations::SelectionSort, impl, numbers);

    quickSortThread.join();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> quickSortDuration = end - start;
    
    selectionSortThread.join();
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> selectionSortDuration = end - start;
    // for (int number : sortedNumbers)
    // {
    //     std::cout << "\n" + std::to_string(number);
    // }

    std::cout<< "Quick Sort Duration: " << quickSortDuration.count() * 1000.0 << "ms" << std::endl;
    std::cout<< "Selection Sort Duration: " << selectionSortDuration.count() * 1000.0 << "ms" << std::endl; 

    return 0;
}
