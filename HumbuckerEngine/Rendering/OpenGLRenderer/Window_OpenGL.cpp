#include "Window_OpenGL.h"

#include <iostream>
#include <ostream>

#include "Utils/Settings.h"

int Rendering_GL::Window_OpenGL::Init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, "Hello World", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	return 0;
}

void Rendering_GL::Window_OpenGL::Cleanup() const
{
	delete &window;
}
