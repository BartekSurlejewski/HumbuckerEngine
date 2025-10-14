#pragma once
#include "Input/InputConstants.h"

class IInputManager
{
	public:
	virtual bool GetKeyDown(InputConstants::KeyCode key) const = 0;
};
