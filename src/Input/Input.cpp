#include "pch.h"
#include "Input.h"

#include "Vulkan/Context/Context.h"

namespace Ash::Input
{
	KeyState GetKey(Key key)
	{
		static std::shared_ptr<Vulkan::Context> context = Vulkan::Context::Get();

		return (KeyState)glfwGetKey(context->Window, (int)key);
	}

	KeyState GetMouseButton(Key mouseButton)
	{
		static std::shared_ptr<Vulkan::Context> context = Vulkan::Context::Get();

		// if (ImGui::GetIO().WantCaptureMouse)
		// {
		// 	return KeyState::Captured;
		// }

		return (KeyState)glfwGetMouseButton(context->Window, (int)mouseButton);
	}

	glm::vec2 GetMousePosition()
	{
		static std::shared_ptr<Vulkan::Context> context = Vulkan::Context::Get();

		double mouseX, mouseY;
		glfwGetCursorPos(context->Window, &mouseX, &mouseY);

		return { mouseX, mouseY };
	}

	void SetCursorMode(CursorMode mode)
	{
		static std::shared_ptr<Vulkan::Context> context = Vulkan::Context::Get();

		glfwSetInputMode(context->Window, GLFW_CURSOR, (int)mode);
	}
}