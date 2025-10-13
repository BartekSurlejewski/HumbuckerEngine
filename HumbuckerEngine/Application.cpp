#include <iostream>
#include <string>
#include <chrono>
#include <mutex>
#include <thread>
#include <vector>
#include <sstream>

#include "AlgorithmsImplementations.h"
#include "Rendering/OpenGLRenderer/Window.h"

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

	Window window;
	window.Init();

	std::cin.get();

	return 0;
}

void Message(std::string message)
{
	static std::mutex coutMutex;
	coutMutex.lock();
	std::cout << message << std::endl;
	coutMutex.unlock();
}
