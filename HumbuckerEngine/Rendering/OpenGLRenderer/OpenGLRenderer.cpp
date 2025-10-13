#include "OpenGLRenderer.h"

#include <iostream>

#include "Utils/Settings.h"

void FramebufferSizeCallback(GLFWwindow *window, int width, int height);

int Rendering_GL::OpenGLRenderer::Init()
{
	// 1. Create and initialize a window
	window = std::make_unique<GL_Window>();
	if (window != NULL)
	{
		if (window->Init() == -1)
		{
			return -1;
		}
	}

	// 2. Initialize GLAD for managing the OpenGL function pointers
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// 3. Set the viewport window size
	glViewport(0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(window->getGLFWWindow(), FramebufferSizeCallback);

	return 0;
}

void Rendering_GL::OpenGLRenderer::Render()
{
	glfwSwapBuffers(window->getGLFWWindow());
	glfwPollEvents();
}

void Rendering_GL::OpenGLRenderer::Terminate()
{
	window->Cleanup();
	glfwTerminate();
}

bool Rendering_GL::OpenGLRenderer::ShouldClose()
{
	return glfwWindowShouldClose(window->getGLFWWindow());
}

std::string Rendering_GL::OpenGLRenderer::GetInfo()
{
	return "OpenGL Renderer\n";
}

void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
	std::cout << "Resized window to " << width << "x" << height << std::endl;
}