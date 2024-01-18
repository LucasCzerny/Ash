#pragma once

namespace Ash::Vulkan
{
	struct Queue
	{
		VkQueue Handle = VK_NULL_HANDLE;
		uint32_t Family = 0;
		
		VkQueue* Pointer() { return &Handle; }
		const VkQueue* Pointer() const { return (const VkQueue*)&Handle; }

		operator VkQueue() const { return Handle; }
	};
}