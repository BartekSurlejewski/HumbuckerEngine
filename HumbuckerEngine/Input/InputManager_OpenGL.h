#pragma once
#include <map>
#include "EngineModules/IInputManager.h"
#include "GLFW/glfw3.h"

namespace Input
{
	class InputManager_OpenGL : public IInputManager
	{
	public:
		explicit InputManager_OpenGL(GLFWwindow *window)
			: window(window){}

		bool GetKeyDown(InputConstants::KeyCode key) const override;
	private:
		GLFWwindow* window;
		std::map<InputConstants::KeyCode, int> keyMap = {
			{InputConstants::ESCAPE, GLFW_KEY_ESCAPE},
			{InputConstants::W, GLFW_KEY_W},
			{InputConstants::S, GLFW_KEY_S},
			{InputConstants::A, GLFW_KEY_A},
			{InputConstants::D, GLFW_KEY_D},
			{InputConstants::SPACE, GLFW_KEY_SPACE},
			{InputConstants::LEFT_SHIFT, GLFW_KEY_LEFT_SHIFT},
			{InputConstants::LEFT_CONTROL, GLFW_KEY_LEFT_CONTROL},
			{InputConstants::Q, GLFW_KEY_Q},
			{InputConstants::E, GLFW_KEY_E}
		};
	};
}