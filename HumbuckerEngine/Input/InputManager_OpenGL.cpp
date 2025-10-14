#include "InputManager_OpenGL.h"

#include "GLFW/glfw3.h"

namespace Input
{
	bool InputManager_OpenGL::GetKeyDown(InputConstants::KeyCode key) const
	{
		auto iterator = keyMap.find(key);
		if (iterator == keyMap.end())
		{
			return false;
		}

		int glfwKeyCode = iterator->second;
		return glfwGetKey(window, glfwKeyCode);
	}
}