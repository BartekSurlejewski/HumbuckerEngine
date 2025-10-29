﻿#include "glad/glad.h"

#include "Renderer_OpenGL.h"
#include <iostream>
#include "Dev/Development_OpenGL.h"
#include "Input/InputManager_OpenGL.h"
#include "Utils/Settings.h"

namespace Rendering_GL
{
	void FramebufferSizeCallback(GLFWwindow *window, int width, int height);

	int Rendering_GL::Renderer_OpenGL::Init()
	{
		// 1. Create and initialize a window
		window = std::make_unique<Window_OpenGL>();
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

		glEnable(GL_DEPTH_TEST);

		return 0;
	}

	void Rendering_GL::Renderer_OpenGL::Tick()
	{
		glClearColor(0.5f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Actual rendering code
		Development_OpenGL::Tick();

		glfwSwapBuffers(window->getGLFWWindow());
		glfwPollEvents();
	}

	void Rendering_GL::Renderer_OpenGL::Terminate()
	{
		window->Cleanup();
		glfwTerminate();
	}

	bool Rendering_GL::Renderer_OpenGL::ShouldClose()
	{
		return glfwWindowShouldClose(window->getGLFWWindow());
	}

	std::string Rendering_GL::Renderer_OpenGL::getInfo()
	{
		return "OpenGL Renderer\n";
	}

	IInputManager *Rendering_GL::Renderer_OpenGL::CreateInputManager() const
	{
		return new Input::InputManager_OpenGL(this->window->getGLFWWindow());
	}

	void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
		std::cout << "Resized window to " << width << "x" << height << std::endl;
	}
}
