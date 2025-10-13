#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.h"

#include <iostream>
#include <ostream>

#include "../../../cmake-build-debug/_deps/glfw-src/include/GLFW/glfw3.h"

void Window::Init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
}
