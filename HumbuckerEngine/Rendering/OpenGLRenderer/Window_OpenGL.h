#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Rendering_GL
{
	// Handles window using GLFW
	class Window_OpenGL
	{
	public:
		Window_OpenGL() = default;
		int Init();
		void Cleanup() const;

		[[nodiscard]] GLFWwindow* getGLFWWindow() const
		{
			return window;
		}

	private:
		GLFWwindow* window;
	};
}
