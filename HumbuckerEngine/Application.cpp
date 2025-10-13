#include <iostream>
#include <string>
#include <chrono>
#include <mutex>
#include <sstream>

#include "EngineModules/IRenderer.h"
#include "Rendering/OpenGLRenderer/OpenGLRenderer.h"

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
		}
		else
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

	// Create and initialize the renderer
	IRenderer *renderer = new Rendering_GL::OpenGLRenderer();
	if (renderer->Init() == 0)
	{
		std::cout << "Renderer initialized successfully." << std::endl;
		std::cout << "Renderer details: " << renderer->GetInfo() << std::endl;
	}
	else
	{
		std::cout << "Failed to initialize renderer." << std::endl;
	}

	// Renderer loop
	while (!renderer->ShouldClose())
	{
		renderer->Render();
	}


	return 0;
}

void Message(std::string message)
{
	static std::mutex coutMutex;
	coutMutex.lock();
	std::cout << message << std::endl;
	coutMutex.unlock();
}
