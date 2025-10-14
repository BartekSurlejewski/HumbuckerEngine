#include <iostream>
#include <string>
#include <chrono>
#include <mutex>
#include <sstream>

#include "EngineModules/IInputManager.h"
#include "EngineModules/IRenderer.h"
#include "Rendering/OpenGLRenderer/Renderer_OpenGL.h"
#include "Input/InputManager_OpenGL.h"

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

	IRenderer *renderer;
	IInputManager *inputManager;

	std::cout << "Hello\n";
	// std::this_thread::sleep_for(1s);

	// Create and initialize the renderer
	renderer = new Rendering_GL::Renderer_OpenGL();

	if (renderer->Init() == 0)
	{
		std::cout << "Renderer initialized successfully." << std::endl;
		std::cout << "Renderer details: " << renderer->getInfo() << std::endl;
	}
	else
	{
		std::cout << "Failed to initialize renderer." << std::endl;
	}

	inputManager = dynamic_cast<Rendering_GL::Renderer_OpenGL*>(renderer)->CreateInputManager();

	// Renderer loop
	while (!renderer->ShouldClose())
	{
		if (inputManager->GetKeyDown(InputConstants::KeyCode::ESCAPE))
		{
			std::cout << "Escape Pressed." << std::endl;
		}

		renderer->Tick();
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
