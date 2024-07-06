#pragma once

#include "Vulkan/Context/Context.h"

namespace Ash::Vulkan
{
	enum class BufferType
	{
		VERTEX, INDEX,
		UBO, SSBO
	};

	class Buffer
	{
	public:
		VkBuffer Handle = VK_NULL_HANDLE;
		VkDeviceMemory Memory = VK_NULL_HANDLE;
		uint32_t Size = 0;
		void* MappedMemory = nullptr;

	public:
		Buffer() = default;
		Buffer(VkBuffer handle, VkDeviceMemory memory, uint32_t size, void* mappedMemory = nullptr);

		Buffer(VkDeviceSize instanceSize, uint32_t instanceCount, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment = 1);
		Buffer(VkDeviceSize instanceSize, uint32_t instanceCount, void* data, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment = 1);

        Buffer(const float* data, size_t size, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment = 1)
            : Buffer(sizeof(float), size, (void*)data, usageFlags, memoryPropertyFlags, minOffsetAlignment) {}

        Buffer(const float* data, size_t size, BufferType type)
            : Buffer(sizeof(float), size, (void*)data, GetUsageFromType(type), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {}

        Buffer(const uint32_t* data, size_t size, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment = 1)
            : Buffer(sizeof(uint32_t), size, (void*)data, usageFlags, memoryPropertyFlags, minOffsetAlignment) {}

        Buffer(const uint32_t* data, size_t size, BufferType type)
            : Buffer(sizeof(uint32_t), size, (void*)data, GetUsageFromType(type), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {}
		
        Buffer(const std::vector<float>& vector, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment = 1)
            : Buffer(sizeof(float), vector.size(), (void*)vector.data(), usageFlags, memoryPropertyFlags, minOffsetAlignment) {}

        Buffer(const std::vector<float>& vector, BufferType type)
            : Buffer(sizeof(float), vector.size(), (void*)vector.data(), GetUsageFromType(type), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {}

        Buffer(const std::vector<uint32_t>& vector, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment = 1)
            : Buffer(sizeof(uint32_t), vector.size(), (void*)vector.data(), usageFlags, memoryPropertyFlags, minOffsetAlignment) {}

        Buffer(const std::vector<uint32_t>& vector, BufferType type)
            : Buffer(sizeof(uint32_t), vector.size(), (void*)vector.data(), GetUsageFromType(type), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {}

        Buffer(const std::vector<glm::vec2>& vector, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment = 1)
            : Buffer(sizeof(float), 2 * vector.size(), (void*)&vector[0][0], usageFlags, memoryPropertyFlags, minOffsetAlignment) {}

        Buffer(const std::vector<glm::vec2>& vector, BufferType type)
            : Buffer(sizeof(float), 2 * vector.size(), (void*)&vector[0][0], GetUsageFromType(type), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {}

        Buffer(const std::vector<glm::vec4>& vector, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment = 1)
            : Buffer(sizeof(float), 4 * vector.size(), (void*)&vector[0][0], usageFlags, memoryPropertyFlags, minOffsetAlignment) {}

        Buffer(const std::vector<glm::vec4>& vector, BufferType type)
            : Buffer(sizeof(float), 4 * vector.size(), (void*)&vector[0][0], GetUsageFromType(type), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {}

		~Buffer();

		Buffer(const Buffer& buffer);
		Buffer(Buffer&& buffer) noexcept;
		Buffer& operator=(const Buffer& buffer);
		Buffer& operator=(Buffer&& buffer) noexcept;

		void Reset();
		bool IsEmpty() const { return Handle == VK_NULL_HANDLE; }

		void CopyData(void* data);

		void Map(uint32_t offset = 0);
		void Unmap();

		VkDescriptorBufferInfo GetDescriptorBufferInfo() const;

		VkBuffer* Pointer() { return &Handle; }
		const VkBuffer* Pointer() const { return (const VkBuffer*)&Handle; }

		operator VkBuffer() const { return Handle; }

		operator bool() const { return !IsEmpty(); }

	private:
		std::shared_ptr<Context> m_Context = nullptr;
		
	private:
		VkDeviceSize GetAlignment(VkDeviceSize instanceSize, VkDeviceSize minOffsetAlignment);
		uint32_t FindMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

		VkBufferUsageFlagBits GetUsageFromType(const BufferType& type);
	};
}
