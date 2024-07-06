#pragma once

#include "Keys.h"

namespace Ash
{
	enum class CursorMode
	{
		Normal = 0x00034001,
		Hidden = 0x00034002,
		Disabled = 0x00034003
	};
}

namespace Ash::Input
{
	KeyState GetKey(Key key);
	KeyState GetMouseButton(Key mouseButton);
	
	glm::vec2 GetMousePosition();
	void SetCursorMode(CursorMode mode);
}