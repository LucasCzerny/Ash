#pragma once

namespace Ash::Vulkan
{
	struct Queue
	{
		VkQueue Handle = VK_NULL_HANDLE;
		uint32_t Family = 0;
		
		operator VkQueue() const { return Handle; }

		VkQueue* Pointer() { return &Handle; }
	};
}