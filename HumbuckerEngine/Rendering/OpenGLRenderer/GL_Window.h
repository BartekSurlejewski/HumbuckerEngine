#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Rendering_GL
{
	// Handles window using GLFW
	class GL_Window
	{
	public:
		GL_Window() = default;
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
