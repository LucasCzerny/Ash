#pragma once

namespace Ash
{
	// if (glfwRawMouseMotionSupported())
    // glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	enum EventType : uint32_t
	{
		WindowClose = 1 << 1,
		WindowResize = 1 << 2,
		WindowFocus = 1 << 3,
		WindowLostFocus = 1 << 4,
		WindowMoved = 1 << 5,
		WindowEvents = 0b11111,

		AppTick = 1 << 6,
		AppUpdate = 1 << 7,
		AppRender = 1 << 8,
		AppEvents = 0b111 << 6,

		KeyPress = 1 << 9,
		KeyRepeat = 1 << 10,
		KeyRelease = 1 << 11,
		KeyEvents = 0b111 << 9,

		MouseMoved = 1 << 12,
		MouseEnter = 1 << 13,
		MouseLeave = 1 << 14,
		MouseButtonPress = 1 << 15,
		MouseButtonRelease = 1 << 16,
		MouseScroll = 1 << 17,
		MouseEvents = 0b111111 << 12,

		// TODO: Gamepad/Joystick support

		FileDrop = 1 << 18
	};
}