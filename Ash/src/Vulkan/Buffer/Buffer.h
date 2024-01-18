#pragma once

#include "Vulkan/Context/Context.h"

namespace Ash::Vulkan
{
	class Buffer
	{
	public:
		VkBuffer Handle = VK_NULL_HANDLE;
		VkDeviceMemory Memory = VK_NULL_HANDLE;
		uint32_t Size = 0;
		void* MappedMemory = nullptr;

	public:
		Buffer() = default;
		~Buffer();

		Buffer(VkDeviceSize instanceSize, uint32_t instanceCount, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment = 1);
		Buffer(VkDeviceSize instanceSize, uint32_t instanceCount, void* data, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment = 1);
		
		template <typename Type>
		Buffer(const std::vector<Type>& vector, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment = 1)
			: Buffer(sizeof(Type), vector.size(), data, usageFlags, memoryPropertyFlags, minOffsetAlignment) {}

		template <typename Type, unsigned int Size>
		Buffer(const std::array<Type, Size>& array, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment = 1)
			: Buffer(sizeof(Type), array.size(), data, usageFlags, memoryPropertyFlags, minOffsetAlignment) {}

		Buffer(VkBuffer handle, VkDeviceMemory memory, uint32_t size, void* mappedMemory = nullptr)
			: Handle(handle), Memory(memory), Size(size), MappedMemory(mappedMemory) {}

		// Not copyable or moveable
		Buffer(const Buffer&) = delete;
		void operator=(const Buffer&) = delete;
		Buffer(Buffer&&) = delete;
		Buffer& operator=(Buffer&&) = delete;

		operator VkBuffer() const { return Handle; }

		void Map(uint32_t offset = 0);
		void Unmap();

	private:
		Context& m_Context = Context::Get();

	private:
		VkDeviceSize GetAlignment(VkDeviceSize instanceSize, VkDeviceSize minOffsetAlignment);
		uint32_t FindMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);
	};
}
